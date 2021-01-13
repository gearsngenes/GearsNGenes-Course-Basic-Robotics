#ifdef _Subscribe2Color
void GnGColorCallBack(GnGColorEvent* colorEventptr)
{
  colorEventptr->printSelf();
  pixels.setPixelColor(0, pixels.Color(colorEventptr->red, colorEventptr->green, colorEventptr->blue));
  pixels.show();
}
#endif
