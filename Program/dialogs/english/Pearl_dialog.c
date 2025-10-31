void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "We have nothing to talk about!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// ==> пиплы в поселении
		case "PearlMan":
			NextDiag.TempNode = "PearlMan";
			dialog.text = NPCStringReactionRepeat("Hello! My name is  "+GetFullName(npchar)+". What can I do for you?","Hello once again!","Guests are very rare in this backwater...","It's such a pleasure to talk to a new face! I'm already sick of all those old snouts...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Oh, nothing...","Me too...","I see...","Heh...",npchar,Dialog.CurrentNode);
			link.l1.go = "PearlMan_1";
		break;
		case "PearlMan_1":
			dialog.text = "We're gathering pearls here, serving  "+NationNameGenitive(sti(npchar.nation))+", you know...";
			link.l1 = "Yeah, I know...";
			link.l1.go = "exit";
			link.l2 = "Hey, listen, is it possible to buy several of these little trinkets directly from the 'producer'? What would you say?";
			link.l2.go = "PearlMan_2";
		break;
		case "PearlMan_2":
			if (rand(10) < 9)
			{
				dialog.text = "Oh no, of course not! The theft of even a single small pearl is punishable by death!";
				link.l1 = "Cruel orders you have here, that's for sure...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Yeah, we have harsh orders here, and one can easily lose his head for any wrongdoings. I am not involved in this, but I can advise you to talk with the local Indians about it. They have somewhere to run away to if anything goes wrong, so they should be bolder than us...";
				link.l1 = "I see... Alright, thanks.";
				link.l1.go = "exit";
			}
		break;
		case "PearlMan_Sharp_1":
			dialog.text = LinkRandPhrase("Are you completely  "+GetSexPhrase("Crazy? Get lost, you idiot","Crazy? Get lost, you stupid fool")+"!",""+GetSexPhrase("What?! Are you out of your mind, you idiot","What?! Are you out of your mind, stupid girl")+"?! Get lost with all your questions...",""+GetSexPhrase("Have you lost your mind, dear? What pirates? Here?! Just get lost, you dimwit","Have you lost your mind, darling? What pirates? Here?! Just get lost, you foolish girl")+"...");
			link.l1 = RandPhraseSimple("No need to be rude...","Watch your tongue!");
			link.l1.go = "exit";
		break;

		// ==> индейцы в поселении
		case "IndPearlMan":
			NextDiag.TempNode = "IndPearlMan";
			dialog.text = NPCStringReactionRepeat(""+GetSexPhrase("Paleface","White squaw")+" wants to talk?","You again, "+GetSexPhrase("paleface","white squaw")+".",""+GetSexPhrase("Paleface likes to talk. He looks like a squaw.","White squaw likes to talk.")+"","Spirits brought my pale face "+GetSexPhrase("brother","sister")+" to me.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Yes.","Yeah, me again.","Very poetic.","I am glad to see you too",npchar,Dialog.CurrentNode);
			link.l1.go = "IndPearlMan_1";
		break;
		case "IndPearlMan_1":
			dialog.text = "Tell me, why have you come?";
			link.l1 = "Oh, nothing in particular, just wanted to hear what you have to say.";
			link.l1.go = "exit";
		break;
		
				
		case "CitizenNotBlade":
			dialog.text = "Captain, what are you doing? Put away your weapon before you cause a lot of trouble!";
			link.l1 = LinkRandPhrase("Fine.","Fine.","Don't worry, I'm already putting it away...");
			link.l1.go = "exit";
		break;  

	}
}
