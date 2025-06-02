// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie pytania masz?","Jak mogę ci pomóc?"),"Próbowałeś zadać mi pytanie jakiś czas temu...","Jeszcze nigdy nie spotkałem ludzi z taką ciekawością na mojej stoczni ani nigdzie indziej w tym mieście.","Co z tymi wszystkimi pytaniami? Moja robota to budowa statków. Zajmijmy się tym.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie...","Nie mam teraz o czym rozmawiać."),"Umph, gdzież to moja pamięć się podziała...","Hm, cóż...","Śmiało...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
