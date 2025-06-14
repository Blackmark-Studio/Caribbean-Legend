void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "What do you want?";
			link.l1 = "Nothing.";
			link.l1.go = "exit";
		break;

		case "Juli":
			dialog.text = "...";
			if (pchar.sex == "woman")
			{
				link.l1 = "Mademoiselle, they say Port-au-Prince loses its charm when you don't smile. Today, it seems, is one of those days. Forgive my frankness, but is something troubling you?";
			}
			else
			{
				link.l1 = "Mademoiselle, tales of your beauty and grace have reached my ears, and I must say—the rumors don't do you justice. They also say Port-au-Prince loses its charm when you don’t smile. Today, alas, seems to be such a day. Name the scoundrel who dared to darken your spirits, and I swear I'll challenge him to a duel to bring back the smile to your lovely face.";
			}
			link.l1.go = "Juli_2";
			DelLandQuestMark(npchar);
		break;

		case "Juli_2":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ah, mademoiselle, your attention is most touching... I must admit, your concern moves me. But alas, the cause of my sorrow is not one that can be dispelled by mere conversation. It is not the fault of any person, but rather circumstances that, I fear, are beyond even the most resolute to overcome.";
				link.l1 = "Circumstances? I assure you, mademoiselle, for "+GetFullName(pchar)+" no obstacle is insurmountable. Tell me what happened—perhaps I can help.";
			}
			else
			{
				dialog.text = "Oh, monsieur, you truly are a master of kind words. I confess, you've almost succeeded in making me smile. But, alas, a duel won’t solve my problem. The one who darkened my day is not a villain, but rather circumstances that even such a gallant gentleman as yourself cannot overcome.";
				link.l1 = "Circumstances? My dear mademoiselle, Captain "+GetFullName(pchar)+" can weather any storm! And should I fail, I swear to you, I shall eat the hat of the first passerby I see!";
			}
			link.l1.go = "Juli_3";
		break;

		case "Juli_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "If you truly insist, I shall tell you what happened. But first, I need your word that this conversation will remain between us alone.";
				link.l1 = "You have my solemn word, mademoiselle. Whatever you tell me shall remain between us, even if I must carry it to the ocean's depths.";
			}
			else
			{
				dialog.text = "Monsieur "+pchar.lastname+", you certainly have the gift of bringing cheer to even the most troubled lady. But please, have mercy on the hats of innocent passersby. If you truly insist, I shall share what happened. Just promise that my words will remain a secret known only to us.";
				link.l1 = "You have my word, mademoiselle, that everything you say to me will be kept in absolute confidence, even under threat of death.";
			}
			link.l1.go = "Juli_4";
		break;
		
		case "Juli_4":
			dialog.text = "Very well. A necklace has vanished from my chambers... but understand, it is far more than a simple trinket. It was bestowed upon me by someone who occupies a cherished place in my heart. Its absence feels like a wound far deeper than the mere loss of a possession\nI have pondered at length who might be responsible, and I can reach but one conclusion. I fear it must be one of my own servants. They alone have access to my private quarters and might covet such a valuable piece. Yet I dare not make this accusation publicly...";
			link.l1 = "A most delicate matter indeed, especially if discretion is your desire. But if I am to offer my assistance, I must understand what forces you to guard this secret so carefully. Without knowing the dangers we face, I might unwittingly lead us both into peril. Tell me whom we must avoid and what threats lurk in the shadows.";
			link.l1.go = "Juli_5";
			if (pchar.sex == "woman")
			{
				link.l2 = "You cannot speak freely? Then I fear, mademoiselle, that I can offer little more than my good wishes. I have neither taste nor talent for intrigue and secrecy. To my thinking, your difficulty could be swiftly resolved with the assistance of the town guard. Yet it seems you've chosen to navigate a more treacherous course through these troubled waters.";
				link.l2.go = "Juli_end";
			}
			else
			{
				link.l2 = "You cannot speak plainly? Then I must beg your forgiveness, mademoiselle, for I find myself utterly powerless in this fog of secrecy. I have little taste for clandestine affairs and shadowy dealings. Your dilemma appears remarkably straightforward: a simple matter for the town guard to resolve. Yet you seem determined to weave it into an intrigue worthy of the royal courts of Europe.";
				link.l2.go = "Juli_end";
			}
		break;

		case "Juli_end":
			dialog.text = "Is this how the renowned Captain "+GetFullName(pchar)+" faces adversity? By retreating at the first sign of complexity? Perhaps your talents would be better employed in counting rum barrels or trading barbs with dockside merchants. I ask only this: if you possess even a shred of honor, keep what I have shared in strictest confidence. Good day to you, Captain.";
			link.l1 = "...";
			link.l1.go = "Juli_end_2";
		break;
		
		case "Juli_end_2":
			DialogExit();
			CloseQuestHeader("UV");
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "Juli_5":
			dialog.text = "You speak wisely, "+GetAddress_Form(NPChar)+". The truth, then: this necklace came from a man whose very existence incurs my uncle's wrath—the governor of the French territories on this island. He has forbidden all contact, even the mere mention of this person's name. Should my uncle discover the origin of this gift, the repercussions would prove disastrous, not only for myself but also for...";
			link.l1 = "Say no more, mademoiselle. I understand perfectly. Rest assured, I shall recover your necklace with the utmost discretion, guarding your secret as jealously as a dragon does its treasure.";
			link.l1.go = "Juli_6";
		break;

		case "Juli_6":
			dialog.text = "You have my deepest gratitude, "+GetSexPhrase("Monsieur "+pchar.lastname+"",""+pchar.name+"")+". Your gallantry and understanding warm my heart in these troubled times. I trust implicitly that my secret lies safe in your keeping. May the winds of fortune fill your sails in this delicate venture.";
			if (pchar.sex == "woman")
			{
				link.l1 = "Fortune embraces those who dare to act, mademoiselle. Rest easy—I shall recover your necklace, as surely as the tide returns to shore.";
			}
			else
			{
				link.l1 = "Fortune smiles upon those with courage, mademoiselle. The moment I recover your precious necklace, it shall be restored to those graceful hands where it rightfully belongs.";
			}
			link.l1.go = "Juli_7";
		break;

		case "Juli_7":
			DialogExit();
			
			NextDiag.CurrentNode = "Juli_7_again";
			AddQuestRecord("UV", "2");
			AddQuestUserData("UV", "sSex", GetSexPhrase("","а"));
			
			pchar.questTemp.UV_Lavochniki = true;
		break;

		case "Juli_7_again":
			if (CheckCharacterItem(PChar, "SM_necklace_Julie"))
			{
				dialog.text = "Ah, Captain, you've returned! Have you news for me? I pray you've recovered my necklace. Please say it's so.";
				link.l1 = "Your troubles are at an end, Julie. The necklace has been recovered, and it gives me the greatest satisfaction to restore it to its rightful place—your delicate hands.";
				link.l1.go = "Juli_22";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Ah, Captain, you've returned! Have you news for me? I pray you've recovered my necklace. Please say it's so.";
				link.l1 = "I regret to disappoint you, Julie. The search continues. But take heart—I shall leave no stone unturned until your precious necklace is restored to you.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Juli_7_again";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "Starpom_1":
			dialog.text = "Greetings, monsieur. What business brings you aboard our vessel?";
			link.l1 = "I seek Captain Tristan Renier; I come bearing a proposition that would line his pockets handsomely.";
			link.l1.go = "Starpom_2_sneak";
			link.l2 = "I must speak with Captain Tristan Renier on a matter of some delicacy—a personal affair, you understand.";
			link.l2.go = "Starpom_2_fortune";
			DelLandQuestMark(npchar);
		break;

		case "Starpom_2_sneak":
			dialog.text = "The captain has gone ashore, I'm afraid. You might find him somewhere in town if your business is urgent.";
			link.l1 = "Might you know his destination? Any particular haunt he favors when visiting this port?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "Starpom_2_fortune":
			dialog.text = "The captain has gone ashore, I'm afraid. You might find him somewhere in town if your business is urgent.";
			link.l1 = "Might you know his destination? Any particular haunt he favors when visiting this port?";
			link.l1.go = "Starpom_3";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Starpom_3":
			dialog.text = "My apologies, "+GetAddress_Form(NPChar)+", but the captain keeps his own counsel regarding his comings and goings. I know only that he disembarked some hours ago.";
			link.l1 = "Even that much is helpful. My thanks for your assistance.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_GoldSeagull_RasprashivaemZhiteley");
		break;

		case "Captain_1":
			if (pchar.sex == "man")
			{
				dialog.text = "Who in blazes are you? By what right do you dare intrude upon my private quarters uninvited?";
				link.l1 = "I am Captain "+GetFullName(pchar)+". And I come on a matter of some importance.";
			}
			else
			{
				dialog.text = "And who might you be, my lady? I don't recall extending any invitations this evening. Though I must confess, some unexpected visitors prove more... intriguing than others. What brings such a vision to my humble accommodations?";
				link.l1 = "I am Captain "+GetFullName(pchar)+". And my visit concerns a matter of business, not pleasure.";
			}
			link.l1.go = "Captain_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Captain_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Business, is it? What manner of affair could possibly warrant such an uncivil interruption?";
				link.l1 = "It's quite straightforward. You possess a necklace that I have come to retrieve.";
			}
			else
			{
				dialog.text = "Business, you say? Most fascinating... What pressing commercial matter would drive a lady of your considerable charms to seek me out in my private chambers?";
				link.l1 = "Spare me your honeyed words, monsieur. I've come for the necklace in your possession. And yes, I know precisely that you have it.";
			}
			link.l1.go = "Captain_3";
		break;

		case "Captain_3":
			if (pchar.sex == "man")
			{
				dialog.text = "Ha! A necklace, you say? Indeed I have acquired such a piece recently, but what concern is that of yours? Surely you don't expect me to surrender my property to the first stranger who demands it?";
			}
			else
			{
				dialog.text = "A necklace? Indeed... I did recently acquire such a trinket. And pray tell, captain, by what means do you propose to relieve me of this piece of jewelry that is rightfully mine?";
			}
			if (sti(pchar.Money) >= 5000)
			{
				link.l1 = "I am prepared to offer you five thousand pesos for the piece. A handsome sum that would allow you to purchase an equally fine ornament, perhaps even grander. Meanwhile, this particular necklace would be restored to one who values it beyond measure—far more than any monetary worth.";
				link.l1.go = "Captain_4_commerce";
			}
			link.l2 = "Let me speak plainly, sir. Your choices have narrowed considerably: surrender the necklace willingly and live to sail another day, or resist and have me retrieve it from your lifeless body. The decision lies with you, but I recommend haste in making it.";
			link.l2.go = "Captain_4_leadership";
		break;

		case "Captain_4_commerce":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				dialog.text = "Five thousand, you say? Well then, Captain, you drive a persuasive bargain. Here, take the bauble if it means so much.";
				link.l1 = "Your wisdom matches your generosity, sir. This decision will not be regretted.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie");
				notification("Check passed", SKILL_COMMERCE);
				GiveItem2Character(pchar, "SM_necklace_Julie");
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddMoneyToCharacter(pchar, -5000);
			}
			else
			{
				dialog.text = "I did not acquire this necklace to barter it away to the first vagabond who flashes coin! It is intended as a gift for my wife, and I'll hear no more on the matter. Remove yourself from my presence before I summon men to escort you out!";
				link.l1 = "If you refuse a gentleman's agreement, then I shall claim what I seek by less civilized means.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Insufficient skill level (25)", SKILL_COMMERCE);
			}
		break;
		
		case "Captain_4_leadership":
			if (GetSummonSkillFromName(pchar, SKILL_Leadership) >= 45)
			{
				dialog.text = "Argh... You insolent pup... Do you think your childish threats will scare me? Ha! You have no idea who you're dealing with!";
				link.l1 = "I don't care who you are. Just hand over the necklace and I'll leave. Or are you really willing to die for a trinket that means nothing to you?";
				link.l1.go = "Captain_4_leadership_2";
				notification("Check passed", SKILL_Leadership);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "I didn’t buy this necklace just to haggle with the likes of you! It was a gift for my wife, and you have no business here. Get out before we throw you out!";
				link.l1 = "If you won’t part with it peacefully, I’ll just take it by force.";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("UV_Ozherelie_Duel");
				notification("Skill not high enough (45)", SKILL_Leadership);
			}
		break;

		case "Captain_4_leadership_2":
			dialog.text = "Damn you and that cursed necklace! Take it. Take it and get out before I change my mind.";
			link.l1 = "A wise decision! Farewell.";
			AddDialogExitQuestFunction("UV_Ozherelie");
			GiveItem2Character(pchar, "SM_necklace_Julie");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "Juli_22":
			dialog.text = ""+pchar.name+", you've brought joy back into my heart! You've returned not just the necklace, but a piece of my soul. Your nobility is admirable, and I promise to tell everyone I can about your valor!";
			link.l1 = "Please, mademoiselle, I didn’t return it for fame. Your smile is the only reward I truly value.";
			link.l1.go = "Juli_23";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

		case "Juli_23":
			dialog.text = "You are so modest, "+pchar.name+". But please, accept this chest of doubloons. Only knowing that you've accepted my gift will make me feel that I have thanked you as you truly deserve.";
			link.l1 = "Please, mademoiselle, don’t insist. Your kind words mean more to me than any chest of doubloons.";
			link.l1.go = "Juli_24_nobility";
			link.l2 = "If it brings you peace, mademoiselle, I will accept your gift. But know that I did not do this for a reward. "+GetSexPhrase("Your recognition","Your gratitude")+" means far more to me than these doubloons.";
			link.l2.go = "Juli_24_chest";
		break;
		
		case "Juli_24_nobility":
			dialog.text = "I completely forgot to ask—do you know who stole the necklace?";
			link.l1 = "All I know, mademoiselle, is that a merchant received it from someone named Giselle. And judging by the circumstances, this may not be the last jewel she plans to sell.";
			link.l1.go = "Juli_25";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;

		case "Juli_24_chest":
			dialog.text = "I completely forgot to ask—do you know who stole the necklace?";
			link.l1 = "All I know, mademoiselle, is that a merchant received it from someone named Giselle. And judging by the circumstances, this may not be the last jewel she plans to sell.";
			link.l1.go = "Juli_25";
			GiveItem2Character(PChar, "chest");
		break;

		case "Juli_25":
			dialog.text = "Giselle? But she's my maid! I had my suspicions... but I didn’t want to believe it. The worst part is, I can't even punish her properly. She could expose my secret—and that’s something I cannot allow.";
			link.l1 = "So what will you do? Let her get away with it and keep stealing from you?";
			link.l1.go = "Juli_26";
		break;

		case "Juli_26":
			dialog.text = "Oh no, of course not. First, I'll make sure she’s no longer anywhere near me. Then I’ll think of a way to punish her so it seems the punishment came from somewhere else.";
			link.l1 = "A woman’s cunning is a dangerous weapon, especially in the hands of someone as refined and perceptive as you. I’m sure your maid doesn’t even realize the game is already lost—and not in her favor.";
			link.l1.go = "Juli_27";
		break;

		case "Juli_27":
			dialog.text = "Ah, captain... I wouldn’t want to resort to tricks, but... sometimes cunning is the only path forward.";
			link.l1 = "Indeed, Julie. I hate to leave you, but duty calls. Who else if not me will look after my crew?";
			link.l1.go = "Juli_28";
		break;

		case "Juli_28":
			dialog.text = "Until we meet again, "+pchar.name+". Please visit our port more often. Our city sorely lacks "+GetSexPhrase("such noble and valiant men as you.","ladies with a heart so noble and a spirit so bold, like yours.")+"";
			link.l1 = "You flatter me, mademoiselle. I promise I won’t miss a single chance to return to your beautiful city. Until next time.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_Juli_GoodEnd");
		break;
		
		case "Juli_31":	
			if (CheckAttribute(pchar, "questTemp.UV_ojerelie_Julie"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = ""+pchar.name+"! What a surprise! Still conquering the seas?";
						link.l1 = "Glad to see you, mademoiselle. Conquering, as best I can, though the sea remains unforgivingly moody. And you—are you enjoying some peace and quiet?";
						link.l1.go = "Juli_32";
					break;

					case 1:
						dialog.text = "Ah, Captain "+pchar.lastname+", how wonderful to see you again! I hope everything is going well for you?";
						link.l1 = "Delighted to see you too, mademoiselle. Business, as always, takes time and effort, but meetings like this brighten any day. And how have your days been?";
						link.l1.go = "Juli_33";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "Captain "+pchar.lastname+", you're back again? Are there really still people in our humble town that you haven't betrayed for a handful of gold coins?";
						link.l1 = "Mademoiselle, I understand your feelings, but I acted as I believed was right. Sometimes the right decision causes pain, and I regret that it hurt you.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;

					case 1:
						dialog.text = "Captain "+pchar.lastname+", again? Is your greed so boundless that you can't leave our town in peace and are hunting for your next victim?";
						link.l1 = "Mademoiselle, I'm sorry my actions caused you pain, but I acted according to my conscience.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Juli_34_zlaya";
					break;
				}
			}
			SetTimerFunction("UV_Julie_HelloAgain", 0, 0, 1);
		break;

		case "Juli_32":	
			dialog.text = "Lately, things have been calm and quiet—nothing disturbs the peace. Please visit our port more often, Captain. I’m sure you’ll find everything you desire here, both in our shop and beyond.";
			link.l1 = "Thank you, mademoiselle. I’ll try to stop by more often. I’m sure your town still holds many pleasant surprises.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;
		
		case "Juli_33":	
			dialog.text = "Thanks to you, captain, my days are much more peaceful now. I do hope you’ll visit us again.";
			link.l1 = "Of course, mademoiselle. Your town always leaves the most pleasant impression. Until next time.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Juli_repeat_residence_1";
		break;

		case "Juli_repeat_residence_1":
			switch (rand(1))
			{
				case 0:
					dialog.text = "Captain "+pchar.lastname+", we meet again. Remarkable, isn't it?";
					link.l1 = "It seems fate is smiling on our encounters today, mademoiselle.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;

				case 1:
					dialog.text = "Captain "+pchar.lastname+", it seems our paths have crossed once more.";
					link.l1 = "Indeed they have, mademoiselle. I'm glad to see you again.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_repeat_residence_1";
				break;
			}
		break;

		case "Juli_34_zlaya":
			switch (rand(1))
			{
				case 0:
					dialog.text = "It seems we’re meeting a bit too often, captain. Or is it that you just can’t stay away from those you’ve already betrayed?";
					link.l1 = "Mademoiselle, our meetings are purely coincidental, but I understand your bitterness. I only hope that one day you’ll understand my reasons.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;

				case 1:
					dialog.text = "What do you want now? Surely your luck isn’t that bad for this to be a coincidence. Or did you just come to remind me of your disgrace?";
					link.l1 = "Mademoiselle, I had no intention of intruding or stirring old wounds. This meeting truly is accidental.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Juli_34_zlaya";
				break;
			}
		break;

		
		
		
		
		
		
		
	}
}