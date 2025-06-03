// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+ GetSexPhrase("my son","my daughter") +"?", "Ask away, I am listening..."), "I am listening, speak now, "+ GetSexPhrase("my son","my daughter") +"...", "For the third time, "+ GetSexPhrase("my son","my daughter") +", ask for what you need.",
                          "A clergyman has a lot of work and you are distracting me, "+ GetSexPhrase("my son","my daughter") +"...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind...", "Not at this time, padre..."), "I have nothing to say, my apologies.",
                      "I'll ask, but later. Forgive me, father.", "Pardon me, holy father...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_pastor"))
			{
				link.l1 = "Holy Father, I wish to speak about Thomas Morrison's daughter.";
                link.l1.go = "dwh_pastor_1";
			}
			if (CheckAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi"))
			{
				link.l1 = "Holy Father, Thomas asked me to tell you that he accepts the path of repentance, will devote himself to good deeds, and will provide the parish with a new bell – no matter the cost.";
                link.l1.go = "dwh_pastor_VD_5";
			}
			// <-- Тёмные воды исцеления
		break;

		// --> Тёмные воды исцеления
		case "dwh_pastor_1":
			dialog.text = "Speak, my child, I am listening.";
			link.l1 = "I know you're against the gypsy helping the girl. But how can you force a father to reject even the slightest chance to save his daughter? Her methods may be questionable, but she has knowledge that might help.";
			link.l1.go = "dwh_pastor_2";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_2":
			dialog.text = "My son, only the Lord can heal the girl. Faith in His plan is what carries us through trials. If Thomas prays diligently, follows God's word, and gives generously to the church, the Lord will hear his prayers and show mercy.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				link.l1 = "(Trustworthy) But even you must admit, the Lord acts through people. What if the gypsy is merely an instrument of His will? What if His design is so profound we mere mortals cannot understand? The Lord works in mysterious ways, does He not?";
				link.l1.go = "dwh_pastor_VD_1";
				notification("Trustworthy", "Trustworthy");
			}
			else
			{
				link.l1 = "You’re forcing a father to watch his daughter waste away, instead of letting him try to save her. Is that merciful?";
				link.l1.go = "dwh_pastor_bez_VD_1";
				notification("Ability not unlocked", "Trustworthy");
			}
		break;

		case "dwh_pastor_VD_1":
			dialog.text = "Your words are wise, Captain. But still, I cannot allow heresy to seep into the heart of our flock and shake the faith of one of its most devout sons.";
			link.l1 = "Nothing would shake his faith more than losing his daughter. But if you allow him to use every means, even those deemed sinful, his faith will grow stronger, not weaker.";
			link.l1.go = "dwh_pastor_VD_2";
		break;

		case "dwh_pastor_VD_2":
			dialog.text = "But... what kind of example would that set for the rest of the congregation?";
			link.l1 = "An example that the church does not punish blindly, but guides and leads toward true repentance. Does Scripture not teach us that sincere repentance and good deeds can redeem sin? A generous donation to the church could be the first step toward redemption.";
			link.l1.go = "dwh_pastor_VD_3";
		break;

		case "dwh_pastor_VD_3":
			dialog.text = "Perhaps you're right, Captain. I am willing to give Thomas this chance. But know this—if he strays from the righteous path and loses his faith, you too will bear responsibility! As for donations—the church has no need of riches, we have what we need. Except... the bell was damaged during the Spanish raid...";
			link.l1 = "I will pass your words to Thomas. Thank you for your time, Holy Father. May the Lord keep you.";
			link.l1.go = "dwh_pastor_VD_4";
		break;

		case "dwh_pastor_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_11";
		break;

		case "dwh_pastor_bez_VD_1":
			dialog.text = "This is not heartlessness, Captain, this is faith. We do not abandon the girl's fate, we place it in the hands of the Lord. If Thomas prays, believes, and waits humbly, I am certain the Lord will hear our prayers and heal her.";
			link.l1 = "You know even the island's nobles, including the governor, have used the gypsy’s services. And they are not excommunicated. So why are you so strict with Thomas?";
			link.l1.go = "dwh_pastor_bez_VD_2";
		break;

		case "dwh_pastor_bez_VD_2":
			dialog.text = "Of course I know, my son. But they are lost souls, not yet touched by the true light of the Lord. Thomas is a pillar of our flock, one of the finest. Allowing evil to chip away at his faith would endanger the whole church, and I cannot allow such a grievous sin.";
			link.l1 = "So you refuse to give even a small chance? Is that truly righteous?";
			link.l1.go = "dwh_pastor_bez_VD_3";
		break;

		case "dwh_pastor_bez_VD_3":
			dialog.text = "What you call salvation might well lead to ruin. I speak from experience. Once, against my will, a healer like her treated my niece. A small girl, she died in agony. And only the Lord knows if her soul was condemned by those rituals. Do not try to convince me—it's futile.";
			link.l1 = "Very well. If that’s your final answer, I will not argue. May the Lord keep you.";
			link.l1.go = "dwh_pastor_bez_VD_4";
		break;

		case "dwh_pastor_bez_VD_4":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor");
			
			AddQuestRecord("DWH", "4");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetCitizenType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_6";
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto23");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			LAi_CharacterEnableDialog(sld);
		break;

		case "dwh_pastor_VD_5":
			dialog.text = "Excellent, my son. A new bell will be a symbol of his devotion to the Lord and the church. Let him do what is needed, but remind him—the eye of the Almighty watches over every deed, and nothing escapes His will.";
			link.l1 = "So be it, Holy Father. Farewell.";
			link.l1.go = "dwh_pastor_VD_6";
			DelLandQuestMark(npchar);
		break;

		case "dwh_pastor_VD_6":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DWH_pastor_PrinesDengi");
			AddLandQuestMark(characterFromId("DWH_Tomas"), "questmarkmain");
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\\MiniEvents\\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_15";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_houseS3", "barmen", "bar1");
			DelLandQuestMark(sld);
		break;
		// <-- Тёмные воды исцеления
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
