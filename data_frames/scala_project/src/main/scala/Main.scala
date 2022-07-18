import org.apache.spark.sql.SparkSession
import org.apache.spark.sql.functions._

case class Point(t: Double, x: Double, y: Double, name: String)

object Main extends App {

  val spark = SparkSession.builder.master("local").appName("Word Count").getOrCreate()
  val sqlContext = spark.sqlContext
  import sqlContext.implicits._

  val makePoint = udf((t: Double, x: Double, y: Double, name: String) => Point(t, x, y, name))
  def calcSlope(a: Option[Point], b: Option[Point]) : Double = {
    var res: Double = 0.0
    if ( a.isDefined && b.isDefined)
    {
      res = (b.get.y - a.get.y)/(b.get.x - a.get.x)
    }
    res
  }
  val udfCalcSlope = udf(calcSlope _)

  val a = new Point(0.0, 1.0, 1.0, "a")
  val b = new Point(1.0, 2.0, 2.0, "b")
  val c = new Point(2.0, 3.0, 3.0, "c")

  val path = Seq(a, b, c)

  val w = org.apache.spark.sql.expressions.Window.orderBy("t")
  val path_frame = path.toDS()
    .withColumn("point", makePoint(col("t"), col("x"), col("y"), col("name")))
    .withColumn("last", lag("point", 1).over(w))
    .withColumn("slope", udfCalcSlope(col("point"), col("last")))
  path_frame.show()

  Thread.sleep(1000) // wait for 1000 millisecond
  spark.stop()
  Thread.sleep(1000) // wait for 1000 millisecond
}
