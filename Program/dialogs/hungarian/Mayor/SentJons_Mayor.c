// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek rád, mi a kérdés?"), "Már másodszor próbálsz kérdezni...", "Ez a harmadik alkalom, hogy megpróbálod megkérdezni...",
                          "Mikor lesz ennek vége?! Elfoglalt ember vagyok, gyarmati ügyekkel foglalkozom, és te még mindig zaklatsz!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Ne most. Rossz helyen és rossz idôben"), "Igaz... De késôbb, nem most...",
                      "Megkérdezem... De egy kicsit késôbb...", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason Дороже золота
			if (CheckAttribute(pchar, "questTemp.GoldenGirl") && pchar.questTemp.GoldenGirl == "antigua")
			{
				link.l1 = "Excellenciás uram, szeretném elmondani, hogy van egy bizonyos információm a Merkúr eltûnésérôl.";
                link.l1.go = "G_Girl";
			}
		break;
		
		// Jason Дороже золота
		case "G_Girl":
			dialog.text = "Információ? Mirôl is?";
			link.l1 = "A brigantiról, excellenciás uram. Postát szállít. Nagy jelentôségû iratokról, meg ilyesmikrôl. Hallottam a nyomozásról, és mint a brit korona hûséges barátja, szeretnék segíteni.";
			link.l1.go = "G_Girl_1";
		break;
		
		case "G_Girl_1":
			dialog.text = "Nagyszerû! Cortney báró nagyon örülni fog a fogadásának! Azonnal összehozok egy találkozót.";
			link.l1 = "Köszönöm, uram. Sietek, és örülnék, ha gyorsan menne.";
			link.l1.go = "G_Girl_2";
		break;
		
		case "G_Girl_2":
			dialog.text = "Ne aggódjon, a világ összes ideje az öné lesz. Ôrség! Fogjátok el!";
			link.l1 = "Köszönöm... várjon, mi? Ez valami vicc?!";
			link.l1.go = "G_Girl_3";
		break;
		
		case "G_Girl_3":
			DialogExit();
			GoldenGirl_AntiguaArest();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
