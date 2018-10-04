object sayHelloTo{
  def sayHelloTo(who:String)={
    println("Hello, " +who)
  }

  def main(args:Array[String]) = {
    for (name <- args) sayHelloTo(name)
  }
}
