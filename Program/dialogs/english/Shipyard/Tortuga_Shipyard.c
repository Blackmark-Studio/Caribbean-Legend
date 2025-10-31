// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you?"),"You tried to ask me a question a little while ago...","I have never met people with such curiosity in my shipyard or anywhere else in this town.","What's with all the questions? My job is to build ships. Let's take care of that.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","Hm, well...","Go ahead...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "tortuga1")
			{
				link.l1 = "I'm looking for Gaius Marchais. The last thing I heard about him was that he docked his galleon, 'Santa Margarita', for you to repair...";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "His own galleon? Ho-ho, that's a good joke, captain. Gaius Marchais owned only a half-dead sloop... he captured a galleon as a prize after he decided to become a privateer. Lucky devil, first raid and such a trophy\nI offered good money for her, but he refused, imagine that! Instead, he sold his pathetic sloop for a small sum and used it to fix the galleon! New sails, new colours and a new name, which is normally not a good sign\nSure, the name was far too papist, but my daughter is also called Margarita, so I suppose it was alright after all... He said he had had enough of violence, so he would become a trader. And he had the good fortune...";
			link.l1 = "Commerce, I suppose, would be restful, but papist galleons don't usually get captured by sloops. And what's his ship's new name now?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "'Admirable'... No wonder! He was just running around his new galleon as if he were chasing a bride, just couldn't stop admiring her.";
			link.l1 = "I see. Is Gaius on Tortuga right now?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "No. He's set sail on his new ship and still hasn't returned to Tortuga. I don't know where he was headed, so I can't give you a hand with this matter.";
			link.l1 = "What an inconvenience... I really need him. We should even have a round of drinks for his 'admirable' ship. Anyway, thanks for the information.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Oh, no problem. Stop by again, captain. And don't forget, there's always a berth for your ship here if you need any repairs!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Guardoftruth", "9");
			pchar.questTemp.Guardoftruth = "tortuga2";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
