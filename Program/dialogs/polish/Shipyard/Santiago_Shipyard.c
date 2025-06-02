// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi pytanie chwilę temu...","Nie spotkałem jeszcze ludzi z taką ciekawością na mojej stoczni ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moim zadaniem jest budować statki. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz o czym rozmawiać."),"Umph, gdzież podziała się moja pamięć...","Hm, cóż...","Śmiało...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
