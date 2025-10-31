// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, "+GetAddress_Form(NPChar)+"?","How can I help you, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, what's the big idea, "+GetAddress_Form(NPChar)+"? ","Again with the strange questions? Darling, go have some rum or something...")+"","Over the course of this day, this is the third time you've brought up this question..."+GetSexPhrase(" Are these signs of affection?","")+"","More questions, I presume. "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind","I've got nothing to talk about at the moment."),"No, not beautiful...","No way, dear...","No, what questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		case "helendrinking":
			dialog.text = "How did you sleep, monsieur? Miss MacArthur ordered us to ensure your complete comfort!";
			link.l1 = "I had a very strange dream...";
			link.l1.go = "helendrinking_1";
		break;

		case "helendrinking_1":
			dialog.text = "Ah!...";
			link.l1 = "What's the matter, mademoiselle? Can I help you with something?";
			link.l1.go = "helendrinking_2";
		break;

		case "helendrinking_2":
			dialog.text = "I'm sorry, Captain... It's a sin, but I can't resist! I'm not very experienced, but don't turn me away, Captain! You're so handsome! I want to please you, to touch...";
			link.l1 = "Indeed, complete comfort... You're also very beautiful! Come on, don't be shy.";
			link.l1.go = "helendrinking_sex";
			link.l2 = "It's better not to touch me right now, mademoiselle – I reek of rum. But you can please me – breakfast would be most welcome!";
			link.l2.go = "helendrinking_nosex";
		break;
		
		case "helendrinking_sex":
			dialog.text = "Oh my, oh my!";
			link.l1 = "";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressSex");
		break;

		case "helendrinking_nosex":
			dialog.text = "Rude!";
			link.l1 = "No breakfast then?";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "exit";
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddDialogExitQuestFunction("HelenDrinking_WaitressNoSex");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
