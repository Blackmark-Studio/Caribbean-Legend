// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What questions do you have?","How can I help you?"),"You tried to ask me a question a little while ago...","I have never met people with such curiosity in my shipyard or anywhere else in this town.","What's with all the questions? My job is to build ships. Let's take care of that.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...","I've got nothing to talk about at the moment."),"Umph, where has my memory gone...","Hm, well...","Go ahead...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратскаЯ линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_2")
            {
                link.l1 = "Listen, master, you build ships here, right?.. And you change sails as well... have you ever thought about... some better sailcloth material?";
                link.l1.go = "mtraxx";
			}
		break;
		
		// Addon 2016-1 Jason пиратскаЯ линейка
		case "mtraxx":
            dialog.text = "You are speaking in riddles, sir... Speak plainly, what brings you here? Nothing to worry about, I'm not some kind of pen pusher and this isn't a custom house.";
			link.l1 = "Ah, I'm glad we're on the same page! Silk sailcloth, sir. As I understand it, there is no better material for sails if speed is your concern.";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Not only speed, but also her ability to sail close to the wind. You are offering ship silk for purchase? It's a valuable cargo, indeed. But there is an obstacle: I simply don't know how to use it in production. Do you follow? A material like this requires a very special set of abilities and skills which I lack. To be honest, my shipyard has a very different specialization; if you had offered me some ropes from the Tsardom of Russia, I'd gladly buy them all, no matter the price. We are in constant need of ropes, however, ship silk is not in demand here, I am sorry!";
			link.l1 = "Hm. I see. Thank you for your time, master. Good luck!";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            DialogExit();
			AddQuestRecord("Roger_2", "4");
			pchar.questTemp.Mtraxx = "silk_3";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
