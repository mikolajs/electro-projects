
import scala.io.Source

def readFile(fileName: String, client:String) = 
  val lista = Source.fromFile(fileName, "utf8").getLines().toList
  lista.map(line => line.replace("\"", "\'")).map(line => s"""$client.println("${line.trim}");""")
  
def saveToFile(fileName: String) = 
  println("todo: save to file")
  
  
@main def main(args:String*) = 
  val file = if(args.size < 1) "index.html" else args(0)
  val client = if(args.size < 2) "client" else args(1)
  println(readFile(file, client).mkString("\n"))
  
