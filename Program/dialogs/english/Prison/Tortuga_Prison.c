// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Speak, I am listening";
			link.l1 = "I was mistaken. Farewell.";
			link.l1.go = "Exit";
		break;
		
		case "tonzag_bail":
			NextDiag.TempNode = "First_officer";
		
			dialog.text = "What is the purpose of your visit to Tortuga, Captain?";
			link.l1 = "I beg you! Help my comrade, and I will answer all your questions!";
			link.l1.go = "tonzag_bail_a";
			link.l2 = "You're such an important person, and you came here without any guards, right after the whole prison heard a gunshot?!";
			link.l2.go = "tonzag_bail_b";
		break;
		
		case "tonzag_bail_a":
			dialog.text = "While you're delaying your answer, he is bleeding out. I repeat the question.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_b":
			dialog.text = "I know enough about what happened. I repeat the question.";
			link.l1 = "";
			link.l1.go = "tonzag_bail_1";
		break;
		
		case "tonzag_bail_1":
			dialog.text = "Last chance, Captain.";
			link.l1 = "I'm carrying out the task assigned to me by the governor-general!";
			link.l1.go = "tonzag_bail_truth";
			link.l2 = "You know very well that I'm the captain of my own ship, and I work on contract. And I visit your lovely island a few times a year!";
			link.l2.go = "tonzag_bail_lies";
		break;
		
		case "tonzag_bail_truth":
			dialog.text = "I had my suspicions, but I wasn't entirely sure. You're lucky that just a few days ago, an important meeting took place in Capsterville. Some very influential people managed to come to an agreement. Thus, you are no longer my enemy.";
			link.l1 = "Will you help us?";
			link.l1.go = "tonzag_bail_truth_1";
			
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
		case "tonzag_bail_truth_1":
			dialog.text = "I'll release you immediately. Your comrade will be transferred to the ship and receive treatment.";
			link.l1 = "Thank you...";
			link.l1.go = "tonzag_bail_truth_2";
		break;
		
		case "tonzag_bail_truth_2":
			dialog.text = "You almost ran aground, Charles! Leave and don't return to Tortuga for at least a month. Allow the dust to settle, and tempers to cool.";
			link.l1 = "I'll do that. Farewell!";
			link.l1.go = "exit";
			link.l2 = "Won't you explain anything at all? Not even a little? ...";
			link.l2.go = "tonzag_bail_truth_3";
		break;
		
		case "tonzag_bail_truth_3":
			dialog.text = "Someone reported you. Allegedly, you're a fanatical Catholic who arrived on our beautiful island to maliciously kill its honourable governor.";
			link.l1 = "I'm not a fanatic!";
			link.l1.go = "tonzag_bail_truth_4";
		break;
		
		case "tonzag_bail_truth_4":
			dialog.text = "It's written skillfully, believe me. I'm good at such things – the best libels are the ones that contain at least a grain of truth in them.";
			link.l1 = "Who wrote the report?";
			link.l1.go = "tonzag_bail_truth_a";
			link.l2 = "Who let the killer into the prison?";
			link.l2.go = "tonzag_bail_truth_b";
		break;
		
		case "tonzag_bail_truth_a":
			dialog.text = "Someone wanted you to be cooped up in the prison for a few days, instead of immediately sending you to the torture table of the Huguenots in the basement of La Roche.\nEnough, Charles. Leave. Deal first with what you've got in front of you, and after... well, you understand me!";
			link.l1 = "Yes. I will. Goodbye, Commandant.";
			link.l1.go = "exit";
		break;
		
		case "tonzag_bail_truth_b":
			dialog.text = "I did.";
			link.l1 = "You'd better send for another one before I leave here.";
			link.l1.go = "tonzag_bail_truth_b_threat";
			link.l2 = "I'm all ears, commandant.";
			link.l2.go = "tonzag_bail_truth_b_charm";
		break;
		
		case "tonzag_bail_truth_b_threat":
			AddComplexSelfExpToScill(100, 100, 100, 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "I am not obliged to explain anything to you, Charles. Be glad that you ended up in my hands and not in the hands of my direct superior. And be glad that your boss will be the one to compensate me for all these disturbances, and not you.";
				link.l1 = "Riiiiiiight... You don't know my boss like I do. So long, commandant.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "You know what? I think I will tell you. A generous, tax-free donation was made to the special garrison pension fund. As a gesture of gratitude, the donor was allowed to contribute to the swift and lawful execution of a notorious criminal!";
				link.l1 = "My officer?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "My friend?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_charm":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 60) {
				dialog.text = "I am not obliged to explain anything to you, Charles. Be glad that you ended up in my hands and not in the hands of my direct superior. And be glad that your boss will be the one to compensate me for all these disturbances, and not you.";
				link.l1 = "Riiiiiiight... You don't know my boss like I do. So long, commandant.";
				link.l1.go = "exit";
				
				Notification_Skill(false, 60, SKILL_LEADERSHIP);
				AddQuestRecord("Tonzag", "3.1");
			} else {
				dialog.text = "You know what? I think I will tell you. A generous, tax-free donation was made to the special garrison pension fund. As a gesture of gratitude, the donor was allowed to contribute to the swift and lawful execution of a notorious criminal!";
				link.l1 = "My officer?";
				link.l1.go = "tonzag_bail_truth_b_1";
				link.l2 = "My friend?";
				link.l2.go = "tonzag_bail_truth_b_1";
				
				Notification_Skill(true, 60, SKILL_LEADERSHIP);
			}
		break;
		
		case "tonzag_bail_truth_b_1":
			dialog.text = "Leave, Charles. And take this scum with you. Your choice of companions... is disappointing.";
			link.l1 = "At least tell me where to find your... benefactor?";
			link.l1.go = "tonzag_bail_truth_b_2";
		break;
		
		case "tonzag_bail_truth_b_2":
			dialog.text = "On the mainland. Goodbye, Charles.";
			link.l1 = "";
			link.l1.go = "exit";
			
			pchar.questTemp.TonzagQuest.KnowMain = true;
			AddQuestRecord("Tonzag", "3.2");
		break;
		
		case "tonzag_bail_lies":
			dialog.text = "A report was made against you. A very nasty one. Captain, you've clearly been set up, but... I'm fully within my authority to keep you here for another couple of weeks and leave your friend to die. Unless...";
			link.l1 = "How much?";
			link.l1.go = "tonzag_bail_lies_a";
			link.l2 = "Who set me up? Did you let the killer into the prison?";
			link.l2.go = "tonzag_bail_lies_b";
			
			AddDialogExitQuestFunction("Tonzag_Bailed");
		break;
		
		case "tonzag_bail_lies_a":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "Please deposit five hundred doubloons into the Tortuga garrison pension fund with the local moneylender.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" And let's add another hundred doubloons for the old trouble you stirred up by getting involved with one high-ranking lady on this island.";
			}
			link.l1 = "Open this damn door already!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bail_lies_b":
			pchar.questTemp.TonzagQuest.Bail = 500;
			dialog.text = "You've already taken up too much of my time. Go to the moneylender and deposit five hundred doubloons into the Tortuga garrison pension fund.";
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "end") {
				pchar.questTemp.TonzagQuest.Bail = 600;
				dialog.text = dialog.text+" And let's add another hundred doubloons for the old trouble you caused by getting involved with a high-ranking lady on this island.";
			}
			link.l1 = "Open this damn door already!";
			link.l1.go = "exit";
			
			AddQuestRecord("Tonzag", "3.3");
		break;
		
		case "tonzag_bailed":
			dialog.text = "";
			link.l1 = "The funds are deposited. Where is Hercule?";
			link.l1.go = "tonzag_bailed_1";
		break;
		
		case "tonzag_bailed_1":
			dialog.text = "We gave him first aid and sent him to your ship. The scoundrel is tough; he'll most likely pull through. Farewell, Captain, and don't let me catch you on our island for a while!";
			link.l1 = "Well, after such a reception, I'll stay well away from here! Farewell, Commandant.";
			link.l1.go = "exit";
			
			NextDiag.TempNode = "First time";
			AddDialogExitQuestFunction("Tonzag_GetOut");
		break;
		
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
