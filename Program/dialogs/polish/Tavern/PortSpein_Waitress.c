// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Pytania, "+GetAddress_Form(NPChar)+"?","Jak mogę ci pomóc, "+GetAddress_Form(NPChar)+"?")," "+GetSexPhrase("Hm, co to za pomysł, "+GetAddress_Form(NPChar)+"? ","Znowu te dziwne pytania? Skarbie, idź napij się rumu czy coś...")+" ","Przez cały ten dzień, to już trzeci raz, gdy mówisz o jakimś pytaniu..."+GetSexPhrase("  To jakieś oznaki zainteresowania?"," ")+" ","Więcej pytań, jak mniemam, "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Zmieniłem zdanie","Nie mam teraz o czym rozmawiać."),"Nie, nie piękna...","Nie ma mowy, kochanie...","Nie, jakie pytania?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
