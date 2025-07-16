// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Pytań, "+GetAddress_Form(NPChar)+"?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?")," "+GetSexPhrase("Hm, co to za wielka intryga, "+GetAddress_Form(NPChar)+"? ","Znowu te dziwne pytania? Skarbie, idź wypij trochę rumu czy coś...")+" Przez cały ten dzień już trzeci raz mówisz o jakimś pytaniu...","Przez cały ten dzień, to już trzeci raz, kiedy mówisz o jakimś pytaniu..."+GetSexPhrase(" Czy to jakieś oznaki uwagi?"," ")+" ","Więcej pytań, jak przypuszczam, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniam zdanie","Nie mam w tej chwili nic do omówienia."),"Nie, nie piękna...","Nie ma mowy, drogi...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
