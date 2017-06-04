/**
  * Created by Knazz on 17.04.2017.
  */
package main.scala

import scala.collection.mutable.ArrayBuffer

object Demo {
  def convert(N: Int): List[String] = {
    val str = N.abs.toBinaryString
    val ost = str.length % 5
    val itogStr = "0" * (5 - ost) + str
    val list = createList(itogStr, 0, itogStr.length / 5, List())
    list
  }

  def createList(itog: String, i: Int, size: Int, list: List[String]): List[String] = {
    if (i == size)
      list
    else {
      val temp = itog.take(5)
      createList(itog.drop(5), i + 1, size, list ++ List(temp))
    }
  }

  def codeTo(s: List[String], i: Int, size: Int, list: List[String]): String = {
    if (i == size)
      list.mkString
    else {
      s(i) match {
        case "00000" => codeTo(s, i + 1, size, list ++ List("011000"))
        case "00001" => codeTo(s, i + 1, size, list ++ List("100010"))
        case "00010" => codeTo(s, i + 1, size, list ++ List("010010"))
        case "00011" => codeTo(s, i + 1, size, list ++ List("110001"))
        case "00100" => codeTo(s, i + 1, size, list ++ List("001010"))
        case "00101" => codeTo(s, i + 1, size, list ++ List("101001"))
        case "00110" => codeTo(s, i + 1, size, list ++ List("011001"))
        case "00111" => codeTo(s, i + 1, size, list ++ List("000111"))
        case "01000" => codeTo(s, i + 1, size, list ++ List("000110"))
        case "01001" => codeTo(s, i + 1, size, list ++ List("100101"))
        case "01010" => codeTo(s, i + 1, size, list ++ List("010101"))
        case "01011" => codeTo(s, i + 1, size, list ++ List("110100"))
        case "01100" => codeTo(s, i + 1, size, list ++ List("001101"))
        case "01101" => codeTo(s, i + 1, size, list ++ List("101100"))
        case "01110" => codeTo(s, i + 1, size, list ++ List("011100"))
        case "01111" => codeTo(s, i + 1, size, list ++ List("101000"))
        case "10000" => codeTo(s, i + 1, size, list ++ List("100100"))
        case "10001" => codeTo(s, i + 1, size, list ++ List("100011"))
        case "10010" => codeTo(s, i + 1, size, list ++ List("010011"))
        case "10011" => codeTo(s, i + 1, size, list ++ List("110010"))
        case "10100" => codeTo(s, i + 1, size, list ++ List("001011"))
        case "10101" => codeTo(s, i + 1, size, list ++ List("101010"))
        case "10110" => codeTo(s, i + 1, size, list ++ List("011010"))
        case "10111" => codeTo(s, i + 1, size, list ++ List("000101"))
        case "11000" => codeTo(s, i + 1, size, list ++ List("001100"))
        case "11001" => codeTo(s, i + 1, size, list ++ List("100110"))
        case "11010" => codeTo(s, i + 1, size, list ++ List("010110"))
        case "11011" => codeTo(s, i + 1, size, list ++ List("001001"))
        case "11100" => codeTo(s, i + 1, size, list ++ List("001110"))
        case "11101" => codeTo(s, i + 1, size, list ++ List("010001"))
        case "11110" => codeTo(s, i + 1, size, list ++ List("100001"))
        case "11111" => codeTo(s, i + 1, size, list ++ List("010100"))
      }
    }
  }
}