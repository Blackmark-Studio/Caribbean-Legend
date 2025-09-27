// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("What kind of questions?","What do you want?");
			link.l1 = RandPhraseSimple("I've changed my mind.'","I've got nothing to say now.");
		    link.l1.go = "exit";
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin") && CheckAttribute(PChar, "questTemp.Terrapin.SJ_count"))
			{
				link.l1 = "I am looking for Mister Jones. Do you know him?";
				link.l1.go = "terrapin";
			}
		break;
		
		case "terrapin":
			if (sti(pchar.questTemp.Terrapin.SJ_count) == 5 || rand(9) == 1) // 10% или числом
			{
				dialog.text = "There are a lot of Joneses here. The most renowned I know of is an aide-de-camp under Colonel Fox, Benjamin Jones. He usually greets visitors at the regiment's headquarters.";
				link.l1 = "Does he have a sister named Molly?";
				link.l1.go = "terrapin_yes";
			}
			else
			{
				dialog.text = LinkRandPhrase("Which Jones do you need? I know at least two dozen of them...","We've got too many Joneses here. You need to be more specific.","There are a lot of Joneses here, as well as Johnsons and Jacksons. You need to be more specific, aye?");
				link.l1 = "He has an adult sister named Molly. I've been told she's a rare beauty.";
				link.l1.go = "terrapin_no";
			}
			npchar.quest.terrapin = "true";
		break;
		
		case "terrapin_no":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Hm, I'm afraid I can't help you with that.","No, I don't know him.","Phah! If the Molly Jones I know is a rare beauty, then Colonel Fox is a parish priest."),LinkRandPhrase("I know a few Molly Joneses. One of them has a brother but... she is not the one you are looking for. Only a man who has been living with apes would call her 'a rare beauty'.","I'm sorry, but all the Joneses I know of don't have sisters.","I'm sorry, I can't help you. Ask someone else."));
			link.l1 = "I see. Sorry for the trouble.";
			link.l1.go = "exit";
			pchar.questTemp.Terrapin.SJ_count = sti(pchar.questTemp.Terrapin.SJ_count)+1;
		break;
		
		case "terrapin_yes":
			dialog.text = "Yes, but she'd be better off as his brother. This strapping lass likely won't find herself a groom because of her ugly mug.";
			link.l1 = "My thanks.";
			link.l1.go = "terrapin_yes_1";
		break;
		
		case "terrapin_yes_1":
			DialogExit();
			AddQuestRecord("Terrapin", "2");
			pchar.questTemp.Terrapin.Benjamin = true;
			DeleteAttribute(pchar, "questTemp.Terrapin.SJ_count");
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Do you think I work for the secret service of "+NationNameGenitive(sti(NPChar.nation))+"?";
			link.l1 = "Well... no. Farewell then.";
			link.l1.go = "exit";
			link.l2 = "Any other questions, then?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Do I look like the investigation bureau? I don't know, I don't know a thing.";

            link.l1 = "You're such a muddlehead! Begone.";
			link.l1.go = "exit";
			link.l2 = "Any other questions, then?";
			link.l2.go = "new question";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
