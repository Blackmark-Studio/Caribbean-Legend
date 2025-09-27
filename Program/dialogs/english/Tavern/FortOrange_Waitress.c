// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Questions, "+GetAddress_Form(NPChar)+"?","How can I help you, "+GetAddress_Form(NPChar)+"?"),""+GetSexPhrase("Hm, what's the big idea, "+GetAddress_Form(NPChar)+"? ","Again with the strange questions? Toots, go have some rum or something...")+"","Over the course of this day, this is the third time you've brought up that question..."+GetSexPhrase(" Are these signs of affection?","")+"","More questions, I presume. "+GetAddress_Form(NPChar)+"?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind","I've got nothing to talk about at the moment."),"No, no, beautiful...","No way, dear...","No, what questions?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_W")
            {
                link.l1 = "Listen, woman, they say you were close to my old mate Francois Gontier. Real close...";
                link.l1.go = "Jamaica_ratW_1";
            }
			
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_WP")
            {
				if (CheckCharacterItem(pchar, "jewelry43"))
				{
					link.l1 = "I've brought your necklace with gems. Here you are. God protect me from grasping women like you in the future.";
					link.l1.go = "Jamaica_ratW_5";
				}
				else
				{
					link.l1 = "Nothing at the moment. I'm looking for your necklace.";
					link.l1.go = "exit";
				}
            }
			
		break;
		
		case "Jamaica_ratW_1":
            dialog.text = "Yes, we were. What of it? I'm not a married woman and I spend time with whom I want. Francois is a very respectable sailor, not like our local fishermen and farmers. He's so... Oh! And he gave me such nice presents!";
            link.l1 = "Alright, that's enough! I know what qualities my mate possesses, you don't have to list them out for me. I don't care what happened between the two of you. You can even get married, I don't care. I need to find him right away, understand? Do you know where he's set off to?";
            link.l1.go = "Jamaica_ratW_2";
        break;
		
		case "Jamaica_ratW_2":
            dialog.text = "Tee hee... You're his messmate, and you don't know where he's gone off to. That's funny!";
            link.l1 = "It's nothing funny, woman. We had agreed to meet in Jamaica and then we had a joint voyage waiting for us... if you understand me. I won't be able to do that alone and he's set off to God knows where!";
            link.l1.go = "Jamaica_ratW_3";
        break;
		
		case "Jamaica_ratW_3":
            dialog.text = "I see. Well, if such a profitable voyage is on the horizon for you, and considering you and Francois are friends... I'll tell you where he's set off to, but for a little reward.";
            link.l1 = "Aye, I know the score. How much do you want?";
            link.l1.go = "Jamaica_ratW_4";
        break;
		
		case "Jamaica_ratW_4":
            dialog.text = "Oh, how venal! I don't need any money. No, I want something special. François promised to give me a lovely necklace with gems. I've already bragged about it to my friends and he's gone straight off... Bring me the pendant and I'll tell you where he has set off to, he-he!";
            link.l1 = "You saucy slut! You Dutch wenches are as greedy as they come! Alright, you'll get your necklace.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_5");
			pchar.questTemp.Slavetrader = "FindRatJamaica_WP";
        break;
		
		case "Jamaica_ratW_5":
            dialog.text = "Ah, it's beautiful! Now my friends will grow green with envy!";
            link.l1 = "Send them my condolences. Now start talking. Where has François set off to?";
            link.l1.go = "Jamaica_ratW_6";
			RemoveItems(PChar, "jewelry43", 1);
        break;
		
		case "Jamaica_ratW_6":
            dialog.text = "Yes, of course, sir. François has sailed off towards Cuba, to Havana.";
            link.l1 = "Thanks for the pricey tip, wench. That's all I wanted.";
            link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_6");
			pchar.questTemp.Slavetrader = "FindRatHavana";
        break;
		
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
