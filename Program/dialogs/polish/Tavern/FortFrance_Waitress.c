// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Pytania, "+GetAddress_Form(NPChar)+"?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, co to za wielki pomysł, "+GetAddress_Form(NPChar)+"? ","Znowu te dziwne pytania? Skarbie, idź się napić rumu czy coś...")+" ","Przez cały ten dzień to już trzeci raz, gdy mówisz o jakimś pytaniu..."+GetSexPhrase("  Czy to jakieś oznaki uwagi?"," ")+"","Więcej pytań, jak mniemam, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie","Nie mam teraz o czym rozmawiać."),"Nie, nie piękna...","Nie ma mowy, kochana...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
