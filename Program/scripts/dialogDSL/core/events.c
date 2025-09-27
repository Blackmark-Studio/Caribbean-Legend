#event_handler("DLGO_ALL", "DLGO_ALL");

// Main function to use with event from dialog files to parse everything on fly
void DLGO_ALL()
{
  aref context = GetEventData();
  aref links, link;
  makearef(links, dialog.links);
  dialog.text = DLGO(dialog.text, &context);
  int linkCount = GetAttributesNum(&links);

  for (int i = 0; i < linkCount; i++) {
    link = GetAttributeN(&links, i);
    string linkName = GetAttributeName(link);
    dialog.links.(linkName) = DLGO(GetAttributeValue(link), &context);
  }
}
