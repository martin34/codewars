import org.apache.spark.sql.SparkSession

// Create the case classes for our domain
case class Department(id: String, name: String)
case class Employee(firstName: String, lastName: String, email: String, salary: Int)
case class DepartmentWithEmployees(department: Department, employees: Seq[Employee])

object Main extends App {

  println("Hello, World!")

  val spark = SparkSession.builder.master("local").appName("Word Count").getOrCreate()
  val sqlContext = spark.sqlContext
  import sqlContext.implicits._

  // Create the Departments
  val department1 = new Department("123456", "Computer Science")
  val department2 = new Department("789012", "Mechanical Engineering")
  val department3 = new Department("345678", "Theater and Drama")
  val department4 = new Department("901234", "Indoor Recreation")

  // Create the Employees
  val employee1 = new Employee("michael", "armbrust", "no-reply@berkeley.edu", 100000)
  val employee2 = new Employee("xiangrui", "meng", "no-reply@stanford.edu", 120000)
  val employee3 = new Employee("matei", null, "no-reply@waterloo.edu", 140000)
  val employee4 = new Employee(null, "wendell", "no-reply@princeton.edu", 160000)
  val employee5 = new Employee("michael", "jackson", "no-reply@neverla.nd", 80000)

  // Create the DepartmentWithEmployees instances from Departments and Employees
  val departmentWithEmployees1 = new DepartmentWithEmployees(department1, Seq(employee1, employee2))
  val departmentWithEmployees2 = new DepartmentWithEmployees(department2, Seq(employee3, employee4))
  val departmentWithEmployees3 = new DepartmentWithEmployees(department3, Seq(employee5, employee4))
  val departmentWithEmployees4 = new DepartmentWithEmployees(department4, Seq(employee2, employee3))

  val departmentsWithEmployeesSeq1 = Seq(departmentWithEmployees1, departmentWithEmployees2)
  val df1 = departmentsWithEmployeesSeq1.toDF()
  df1.show()

  val departmentsWithEmployeesSeq2 = Seq(departmentWithEmployees3, departmentWithEmployees4)
  val df2 = departmentsWithEmployeesSeq2.toDF()
  df2.show()

  val all = df1.union(df2)
  all.show()

  import org.apache.spark.sql.functions._
  val w = org.apache.spark.sql.expressions.Window.orderBy("salary")
  val employees = all.select(explode($"employees")).select($"col.*").distinct().withColumn("prevSalary", lag("salary", 1, 0).over(w)).withColumn("diff", col("salary") - col("prevSalary"))
  employees.show()
  employees.filter(col("diff") === 80000).show()

  val p = Seq(120000, 140000)
  for( v <- p )
  {
    val upper = v + 20000
    val lower = v - 20000
    employees.filter(col("salary") > lower && col("salary") < upper).show()
  }



  Thread.sleep(1000) // wait for 1000 millisecond
  spark.stop()
  Thread.sleep(1000) // wait for 1000 millisecond
}
