// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Jakie masz pytania?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),"Próbowałeś zadać mi jakieś pytanie niedawno, "+GetAddress_Form(NPChar)+"...","Przez cały ten dzień to już trzeci raz, gdy mówisz o jakimś pytaniu...","Więcej pytań, jak mniemam?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie...","Nie mam teraz nic do omówienia."),"Umph, gdzież to moja pamięć się podziała...","Tak, to naprawdę już trzeci raz...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
