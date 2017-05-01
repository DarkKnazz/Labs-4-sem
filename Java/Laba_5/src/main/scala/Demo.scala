/**
  * Created by Knazz on 17.04.2017.
  */
package main.scala
object Demo {
  def notTailRec(a: Double, b: Double): List[Int] ={
    if((math rint (a + 1)).toInt >= (math rint b).toInt)
      List()
    else List((math rint (a + 1)).toInt) ++ notTailRec((math rint (a + 1)).toInt, (math rint b).toInt)
  }

  def tailRecNumbers(a: Double, b: Double, list: List[Int]): List[Int] ={
    if((math rint (a + 1)).toInt >= (math rint b).toInt)
      list
    else tailRecNumbers((math rint (a + 1)).toInt, (math rint b).toInt, list ++ List((math rint (a + 1)).toInt))
  }
}
