// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What do you want? Ask away.","I'm listening, what's the question?"),"This is the second time you've tried to ask...","This is the third time you've tried to ask...","When is this going to end?! I am a busy man, working on colony matters, and you are still bothering me!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind, sorry.","Not now. Wrong place and time."),"True, I have nothing to say right now, sorry.","I'll ask later.","I am sorry, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "quest.Guardoftruth") && CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && pchar.questTemp.Guardoftruth.Trinidad == "begin")
			{
				link.l1 = "Your Excellency, there was a frigate under the command of Miguel Dichoso in April 1654. He has disappeared since then. Do you remember anything about him? Perhaps he visited you, had a conversation...";
				link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Yes, I remember that man. But I don't recall any details about him. He came here and then he just left. I can't help you.";
			link.l1 = "I see. Sorry for troubling you.";
			link.l1.go = "exit";
			npchar.quest.guardoftruth = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
