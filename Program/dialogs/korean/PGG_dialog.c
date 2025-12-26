#include "DIALOGS\%language%\Common_Duel.c"

#define MAX_PGG_STORIES 		9
#define MAX_PGG_QUEST_STORIES 	3
#define MAX_PGG_MEET_REP 		5

string PGG_Stories[MAX_PGG_STORIES] = {
"... only devil and I know the location and the last man standing will take it all!\n",
"... and Maynard said: 'I don't expect mercy so shouldn't you'.\n",
"... he was that drunk that proposed to arrange the very special hell right there, just to see who of us will endure it longer.\n",
"... funny story of my old pal from Porto Belo...\n",
"... No, gentlemen, those are crappy anecdotes. I've got some good stories to fill your ears\n",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!\n",
"... I tend to believe that this 'Flying Dutchman' crap is a fake\n",
"... Ever heard about me being shell shocked at Key West? Although there was no visible damage, I lain for two months. And then my passion persuaded me to confess. They say, with God's help, the matter will go well ... Well, I went, and the priest asked: 'Did you kill many people, my son?' 'And how many ships sunk?' - 'Many' - I answer. And he does not let up: 'Have you seduced many wives?' Then I say: 'Padre, I did not come here to brag'. Ha-ha-ha-ha\n",
"... But in Santa Cruz there was a case during mooring. With a cry of 'Beware!' My sailor throws a whip and hits the local onlooker straight in the forehead! That screams and falls without feelings. The sailor was frightened, not waiting for the ramp he jumped on the pier and gave that poor guy some water. Finally, he woke up and told the sailor: 'You have to shout 'Watch out' when danger is coming, not 'Beware' you idiot! Ha-ha-ha! " 
};

string PGG_QuestStories[MAX_PGG_QUEST_STORIES] = {
"... Got stuck in Florida once...",
"... Can't say much about the 'Flying Dutchman'. Never seen it. I once boarded some odd brigantine, empty, not a single soul onboard. Guess what? 1700 barrels of fine wine in her hold!.. That is what I call luck!...",
"... She killed the poor bastard right in the middle of the tavern after he suggested testing her 'officer skills' upstairs..."
}

string PGG_Meet_GoodRep[MAX_PGG_MEET_REP] = {
"Decent captains are rare breed in these waters.",
"Nobility is out of fashion these days.",
"Oh, now there's a decent captain, not like you at all, cutthroats! He-he!",
"Gentlemen, we have a decent captain at our table, who had been through fire and water countless times. So, what can you tell us, esteemed one?",
"Now there's another glorious corsair, who is not used to look for royal roads.", 
};

string PGG_Meet_BadRep[MAX_PGG_MEET_REP] = {
"Now there's another pirate!",
"Gentlemen, we have a gentleman of fortune at our table, I guess?",
"I smell gunpowder and blood! A filibuster aboard!",
"Ohh, gentlemen, now this is a seasoned corsair, who surely has something to tell in a nice company over a mug of rum... Would you like to join us?",
"Oh, I smell gunpowder... Gentlemen, we now have here another glorious corsair, who sure as hell will have a lot to tell on his confession... Ha-ha-ha!",
};

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
   	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch(Dialog.CurrentNode)
	{
//	Dialog.Text = "버그를 발견하셨군요... 해군을 위해 QA팀에 꼭 보고해 주십시오.";
//	link.l1 = "물론이지!";
//	link.l1.go = "exit.";
	case "First time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "이봐, 꺼져, 안 그러겠어! 내 거래 망치면 네 심장을 쥐어뜯어버릴 거야!";
			link.l1 = RandPhraseSimple("감히 나를 협박하겠다고, 이 쥐새끼야?!","네 말에 목이 메이게 해주마, 이 악당아!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "아, 그렇군. 장사는 장사지. 행운을 빌어.";
			link.l2.go = "Exit";
			break;
		}
//		Dialog.Text = "안녕하세요, 제 이름은 "+GetFullName(NPChar)+", 그리고 너는?";
		if(rand(10) == 3)
		{
			iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
			Dialog.Text = PGG_QuestStories[iRnd];
		}
		else
		{
			iRnd = rand(MAX_PGG_STORIES - 1);
			iAns = rand(MAX_PGG_MEET_REP - 1);
			Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns],PGG_Meet_BadRep[iAns]);
		}		 
//		link.l1 = "내 이름은 "+GetFullName(pchar)+".";
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("모두에게 술이다! 내가 선장이야 "+GetFullName(pchar)+".","나는 '의 선장이오"+PChar.Ship.Name+" 그리고 몇백 명의 진짜 악마들도 있지! 헤헤! 내 이름은 "+GetFullName(pchar)+"."),RandPhraseSimple("신사 여러분, 제 소개를 하겠습니다. 저는 선장입니다 "+GetFullName(pchar)+".","아직 소개를 못 받았군. 나는 '의 선장이오"+PChar.Ship.Name+" 깃발 아래에서 "+NationNameGenitive(sti(PChar.nation))+". 내 이름은 "+GetFullName(pchar)+"."));
		link.l1.go = "Meeting";
		break;

	case "Meeting":
		Dialog.Text = "여기 있는 모두가 나를 잘 알지! 나는 "+GetFullName(NPChar)+". 만나서 반갑소! 무엇을 도와드릴까요?";
		link.l1 = RandPhraseSimple("너랑 볼일이 있어!","너와 얘기하고 싶어...");
		link.l1.go = "quest";
		if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
		{
			sld = GetRealShip(sti(NPChar.Ship.Type));
			
			Dialog.Text = "여기 있는 모두가 나를 잘 알지! 나는 "+GetFullName(NPChar)+", 선장님 "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+".";
			link.l2 = "나랑 함께하지 않겠나? 배가 두 척이면 한 척보다 낫지. 우리 같이 장사하면 잘될 거야.";
			link.l2.go = "companion";
		}
		if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
		{
			link.l3 = RandPhraseSimple("내 배에서 장교로 일하고 싶나?","내 배에서 장교로 일하면 잘할 것 같은데. 어때?");
			link.l3.go = "officer";
		}
		if (bBettaTestMode)
		{
			link.l7 = "(베타 테스트) 퀘스트.";
			link.l7.go = "BT_Quest";
			link.l8 = "(베타 테스트) 결투.";
			link.l8.go = "outraged";
		}
		link.l9 = "아무것도 아니다.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		NPChar.meeting = true;
		break;

	case "Second time":
		if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			Dialog.text = "이봐, 꺼져, 안 그러겠어! 내 거래 망치면 네 심장을 찢어버릴 거야!";
			link.l1 = RandPhraseSimple("네가 감히 나를 협박해, 이 쓸개 빠진 놈아?!","네 말에 목이 메이게 해주마, 이 악당아!");
			link.l1.go = "Exit_Smugglers_Fight";
			link.l2 = "아, 그렇군. 사업은 사업이지. 행운을 빌어.";
			link.l2.go = "Exit";
			break;
		}

		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "오늘은 이미 다 말했어!";
			link.l1 = "아, 그래...";
			link.l1.go = "exit";
			break;
		}

		Dialog.text = RandPhraseSimple("무슨 일이야"+GetFullName(pchar)+"?","누구야? 아, 너였군... 꺼져, 지금 기분 아니니까...");
		link.l1 = RandPhraseSimple("장사는 어떤가?","당신과 이야기하고 싶었어...");
		link.l1.go = "quest";

		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
		{
//			Dialog.Text = RandPhraseSimple("오, 이게 누구야! 바로 "+GetFullName(pchar)+". 소식 있나?","어떻게 지내십니까? 무엇을 도와드릴까요?");
			if(rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories[iRnd]+PCharRepPhrase(" 무슨 소식이야?"," 이 군도 주변에 무슨 소식이 있지?");
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories[iRnd]+PCharRepPhrase(PGG_Meet_GoodRep[iAns]+" 무슨 소식이야?",PGG_Meet_BadRep[iAns]+" 이 군도에 무슨 소식이 있나?");
			}		
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l2 = RandPhraseSimple("나랑 함께하지 않겠나? 배가 두 척이면 한 척보다 낫지. 우리 같이 장사하면 잘될 거야.","경험 많은 선장처럼 보이는데. 내 깃발 아래에서 항해할 생각 있나?");
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				Dialog.Text = RandPhraseSimple("아이고, 이럴 수가... 내 배가 침몰했어!","이게 누구야?! 무슨 일로 여기 온 거지? 그런데 말이야, 내 배를 잃어버렸어...");
				link.l3 = RandPhraseSimple("안타깝군. 다음엔 더 운이 좋을지도 몰라.","그렇군... 이제 나는 가봐야겠어. 또 보자.");
				link.l3.go = "exit";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l3 = RandPhraseSimple("내 배에서 장교로 일하고 싶나?","내 배에서 장교로 일하면 잘할 것 같군. 어때?");
					link.l3.go = "officer";
				}
			}
//			link.l4 = "무슨 소식이야?";
//			link.l4.go = "rumours_capitan";
		}
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
		{
			link.l8 = PCharRepPhrase("정말 못생긴 주둥이군. 한 대 맞아야 정신 차릴 것 같다.","오, 우리 '친구'님이군. 가슴에 구멍 몇 개 더 뚫어줄까?");
			link.l8.go = "outraged";
		}
		link.l9 = "아무것도 아니야.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Second time";
		break;

	case "no_ship":
		break;

//==================================================
// Officer 
//==================================================
	case "officer":
		//раз в день.
		if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("이미 말했잖아, 난 관심 없어.","우리는 이미 모든 것을 다 이야기한 줄 알았어.");
			link.l1 = RandPhraseSimple("어떻게 잊을 수 있겠어?","그렇군. 잘 가.");
			link.l1.go = "exit";
			break;
		}
		//если уже был офицером, то посылает нафиг.
		if (CheckAttribute(NPChar, "PGGAi.Officer"))
		{
			Dialog.Text = RandPhraseSimple("흠... 아마도 아니야. 두 번은 안 돼.","네가 내가 그 미끼를 두 번이나 물 거라고 생각했어?!");
			link.l1 = RandPhraseSimple("그래, 원하는 대로 해...","알겠어. 그럼 또 보자.");
			link.l1.go = "exit";
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("흠... 아니, 그렇지 않은 것 같군.","아니, 나는 선장이고, 장교로 복무하고 싶지 않아.");
			link.l1 = RandPhraseSimple("그래, 원하는 대로 하시게...","알겠어. 그럼, 또 보자.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
			break;
		}
		//Проверка на ПИРАТЕС, не было! :) //navy 04.04.07
		if (FindFreeRandomOfficer() < 1)
		{
			Dialog.Text = RandPhraseSimple("이미 한 세트 다 가지고 있잖아.","내가 네 명령을 들을 준비가 됐다고는 생각하지 않아.");
			link.l1 = RandPhraseSimple("안됐군...","음, 운명이 달리 정했지.");
			link.l1.go = "exit";
			break;
		}
		if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
		{
			NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank)*500*MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)*1000);
		}
		Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("딱 내가 필요했던 거야! 우리 칼이 적들의 피를 맛보게 될 거다! 하지만 한 가지 문제가 있어 - 아직 내가 필요한 게 남았어 "+NPChar.Quest.Officer.Price+" 내 빚을 갚을 페소.","넌 진짜 노련한 뱃사람처럼 보이네. 그리고 돈만 낼 생각이 있다면 "+NPChar.Quest.Officer.Price+" 페소라면, 우리 잘 협력할 수 있을 것 같군."),LinkRandPhrase("당신의 제안이 꽤나 영광스럽군요. 아주 적은 보수로 당신을 위해 일하는 것에 동의하겠소 "+NPChar.Quest.Officer.Price+" 페소입니다.","흠... 너 보아하니 노련한 뱃사람이군. 돈을 낼 생각이 있다면 네 제안을 받아들여야겠어 "+NPChar.Quest.Officer.Price+" 페소입니다.","우린 잘 협력할 수 있을 것 같소, 선장님. 그냥 "+NPChar.Quest.Officer.Price+" 페소면 거래 성사야."));

		MakeRandomLinkOrderTwo(link, PCharRepPhrase(RandSwear() + RandPhraseSimple("That suits me fine. I just hope you're not going to charge me on daily basis.", "That's very expensive, but I hope you're worth it."), 
				LinkRandPhrase("I agree. Consider yourself a part of the crew.", "Hm... I think, I can afford it.", "Looks like you are worth it. Take the coins!")), "officer_hired",
									PCharRepPhrase(RandSwear() + RandPhraseSimple("You're not worth that much. See you...", "Too damn expensive for me."), 
				LinkRandPhrase("Yeah... Greed is not a sin...", "Are you laughing at me? I can buy a dozen like you for such money.", "That's a rip off. Where am I supposed to find such money?")), "exit");
		link.l3 = "흠... 그런데 너는 얼마나 자격이 있지?";
		link.l3.go = "Exit_ShowParam";
		break;

	case "officer_hired":
		if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
		{
			Dialog.Text = "선장, 돈이 좀 부족한 것 같은데.";
			link.l1 = "오... 정말이군.";
			link.l1.go = "exit";
			break;
		}
		pchar.questTemp.HiringOfficerIDX = NPChar.index;
		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
		AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
		NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0)*0.3)

		DeleteAttribute(NPChar, "Quest.Officer");
		DeleteAttribute(NPChar, "PGGAi.Task");
		DeleteAttribute(NPChar, "PGGAi.LockService");

		Dialog.Text = RandPhraseSimple("훌륭하군!","나는 당신을 한 번도 의심하지 않았소, 선장님.");
		link.l1 = "출항에 늦지 마라.";
		link.l1.go = "exit";
		break;

//==================================================
// Companion 
//==================================================
	case "companion":
		Dialog.Text = "버그 발생, 개발자에게 알리시오";
		link.l1 = "내가 할게!";
		link.l1.go = "exit";
		//раз в день.
		if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
		{
			Dialog.Text = RandPhraseSimple("이미 말했잖아, 난 관심 없어.","우리는 이미 모든 것을 다 이야기한 줄 알았어.");
			link.l1 = RandPhraseSimple("어떻게 잊을 수 있겠어?","그렇군. 잘 가.");
			link.l1.go = "exit";
			break;
		}
		//разница в один класс.. нефиг халявить
		if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar)-1)
		{
			Dialog.Text = RandPhraseSimple("너랑 같이 항해하자고?! 먼저 좀 철들고 와!","난 그거엔 관심 없는 것 같아!");
			link.l1 = RandPhraseSimple("그래, 원하는 대로 하시오...","알겠어. 그럼, 또 보자.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//если отношение ниже 70, то в 70% случаев откажет...
		if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && rand(100) < 70)
		{
			Dialog.Text = RandPhraseSimple("흠... 아니, 그렇지 않은 것 같군.","아니, 고맙소. 난 누구 밑에서 일하는 건 싫소.");
			link.l1 = RandPhraseSimple("글쎄, 원하시는 대로 하십시오...","알겠어. 그럼, 또 보자.");
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
			break;
		}
		//есть ли место для компаньона.
		if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
		{
			Dialog.Text = NPCharRepPhrase(NPChar,RandSwear()+RandPhraseSimple("너 마음에 들어! 거래 성사야! 벌써 우리 주머니에서 페소가 짤랑거리는 소리가 들리는군!","똑똑한 녀석이군 "+GetSexPhrase("녀석","아가씨")+"... 우리 잘 협력할 수 있을 거야!"),LinkRandPhrase("네 제안 마음에 들어. 동의하지.","흥미롭군. 있잖아, 우리 함께라면 더 큰 성과를 낼 수 있을 것 같아!","재미있겠군. 거래 성사다!"));
			link.l1 = RandPhraseSimple("좋아! 바다에서 기다릴게!","거래지! 우리 멋진 선원이 될 거야.");
			link.l1.go = "exit";
			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			NPChar.Dialog.TempNode = "hired";
			NPChar.Dialog.FileName = "Enc_Officer_dialog.c";
            NPChar.Payment = true;
            NPChar.Money   = 0;
            
            SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
    
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			SetCharacterRemovable(NPChar, true);
			SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
		}
		else
		{
			Dialog.Text = RandPhraseSimple("이미 동료가 충분히 있다고 생각해.","이미 배가 충분한데, 왜 더 필요하지?");
			link.l1 = "그래... 아마 네 말이 맞을 거야.";
			link.l1.go = "exit";
		}
		break;

	case "companion_leave":
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("너랑 있으면 지겨워!!! 네 함대를 떠날 거야!","내 인내심은 끝났다! 나는 떠난다."),RandPhraseSimple("네 '제독'님... 당신의 만행에 질렸소. 이제 물러가겠소.","네 지휘는 이제 지긋지긋해서 나는 네 함대를 떠난다."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("좋아, 그럼 꺼져.","알겠어, 어디든 네가 가고 싶은 데로 가."),RandPhraseSimple("좋아. 더 이상 붙잡지 않겠다.","그건 네 선택이야. 순풍이 불길 바란다."));
		link.l1.go = "Exit_Companion_Leave";
		link.l2 = PCharRepPhrase(RandPhraseSimple("에흠... 조금 더 얹어주는 건 어때?","카람바! 이런, 혹시 머물러 줄 수 있겠나? 선원들에게도 수고비를 좀 더 줄 수 있소!"),RandPhraseSimple("당신과 헤어지는 건 정말 싫군... 혹시 작은 보상으로 우리 갈등을 해결할 수 있지 않을까?","임금을 올려주는 건 어때?"));
		link.l2.go = "companion_stay";
		break;

	case "companion_stay":
		if (CheckAttribute(NPChar, "Quest.Companion"))
		{
			Dialog.Text = RandPhraseSimple("한 번이면 충분했어. 이제 더 이상 네 약속을 믿지 않겠다!","돈으로는 나를 유혹할 수 없어! 내 결정은 최종이야!");
			link.l1 = RandPhraseSimple("좋아, 행운을 빌어.","그럼 꺼져라, 다시는 내 앞에 나타나지 마!");
			link.l1.go = "Exit_Companion_Leave";
			break;
		}
		NPChar.Quest.Companion.Price = 2*GetSalaryForShip(NPChar);
		Dialog.Text = RandSwear()+" "+NPCharRepPhrase(NPChar,RandPhraseSimple("프리미엄이라고? 좋아! 금액은 "+NPChar.Quest.Companion.Price+" 페소면 충분하겠어.","글쎄, 아마도 네가 내 선원들에게 돈을 줄 준비가 되어 있다면\n "+NPChar.Quest.Companion.Price+" 페소만 준다면, 놈들을 붙잡아 둘 수 있을지도 몰라."),RandPhraseSimple("좋아! 소정의 비용만 내면 머물 수 있어 "+NPChar.Quest.Companion.Price+" 페소!",NPChar.Quest.Companion.Price+" 한동안 나와 내 선원들을 만족시켜 줄 거야."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("나 비웃는 거야, 뭐야?! 당장 꺼져!","하! 이 돈은 훨씬 더 쓸모 있는 데 쓰는 게 낫지!"),RandPhraseSimple("오, 이런. 난 그렇게 부자가 아니야!","안녕히 계시오. 이만큼 지불하겠소."));
		link.l1.go = "Exit_Companion_Leave";
		if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("훌륭하군! 여기 네 상여금이다!","나는 이 모든 게 결국 돈 때문이라는 걸 한 번도 의심한 적 없어!"),RandPhraseSimple("훌륭하군! 네가 머물게 되어 기쁘다.","약속했던 것을 여기 가져왔소."));
			link.l2.go = "Exit_Companion_Stay";
		}
		break;

	case "Exit_Companion_Leave":
		chrDisableReloadToLocation = false;
		RemoveCharacterCompanion(pchar, NPChar);

		NPChar.PGGAi.IsPGG = true;
		NPChar.RebirthPhantom = true;
		NPChar.PGGAi.location.town = GetCurrentTown();

		LAi_SetWarriorTypeNoGroup(NPChar);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();
		break;

	case "Exit_Companion_Stay":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

//==================================================
// Quests
//==================================================
//==== BETTA_TEST ====
	case "BT_Quest":
		Dialog.Text = "템플릿을 선택하세요!";
		link.l1 = "퀘스트 1 템플릿 - 바다.";
		link.l1.go = "BT_Quest_1";
		link.l2 = "선택됨! 퀘스트 1 템플릿 - 육지.";
		link.l2.go = "BT_Quest_2";
		break;

	case "BT_Quest_1":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
		Dialog.Text = "퀘스트 1 템플릿 - 바다.";
		link.l1 = "아, 그래...";
		link.l1.go = "quest";
		break;
	case "BT_Quest_2":
		NPChar.PGGAi.ActiveQuest.QstNumber = 0;
		NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
		Dialog.Text = "선택됨! 퀘스트 1 템플릿 - 육지.";
		link.l1 = "아, 그래...";
		link.l1.go = "quest";
		break;
//==== BETTA_TEST ====

	case "quest":
		chrDisableReloadToLocation = false;
		if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
		{
			Dialog.Text = "나는 이미 전부 말했어!";
			link.l1 = "아, 그래...";
			link.l1.go = "exit";
			break;
		}
		Dialog.Text = RandPhraseSimple("무슨 일이야?.. 힉! 안 보여? 나랑 녀석들이 신나게 놀고 있잖아!.. 힉...","에이... 오늘은 장사가 안 되네!");
		link.l1 = "그렇군...";
		link.l1.go = "exit";
		if (!PGG_IsQuestAvaible()) break; //квест нельзя брать.
		//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квеста, который хочет от нас ПГГ
		if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // может и не быть
		switch (iRnd)
		{
		case 0:
			if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				//квест от ПГГ
				/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{ */
				if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
				{  // не занят другими квестами ПГГ
					Dialog.Text = "무슨 얘기지? 뭐, 때마침 잘 왔군. 일이라면 언제든 준비되어 있지!";
					link.l1 = "흠. 무슨 말을 하는 거지?";
					link.l1.go = "Quest_1_Work";
					NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
					PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
				}
				/* }
				//квест от ГГ
				else
				{
					if ()
					{
						Log_TestInfo("The test sentence of the protagonist");

						Dialog.Text = LinkRandPhrase("...그곳을 아는 건 악마와 나뿐이야, 그리고 마지막까지 살아남는 자가 모든 걸 가지게 되지!..","...그리고 마이나르트가 대답했다: '너에게 자비를 기대하지 않으니, 나 또한 자비를 베풀지 않겠다'","...그리고 망망대해로 나가서 이미 술에 좀 취했을 때, 그가 이렇게 제안했지. '거기서 한판 뒤집어 놓고 누가 끝까지 버티는지 보자고.'")+PCharRepPhrase(LinkRandPhrase("또 다른 해적이 나타났군!","신사 여러분, 우리 테이블에 혹시 행운의 신사가 계신가요?","화약 냄새랑 피 냄새가 난다! 우현에 필리버스터다!"),LinkRandPhrase("이 바다에서는 제대로 된 선장들이 드물지.","요즘은 귀족이 유행이 아니지.","오, 이제야 제대로 된 선장이 나타났군, 너희 같은 칼잡이들하고는 다르지! 헤헤!"));
						link.l1 = "나는 소리치는 게 아니야, 말하는 거야 - 이익이 되는 거래가 있다고!";
						link.l1.go = "Quest_1_Work";
					}
				}  /**/
			}
			break;
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	case "quest_onStay": // ПГГ сам подходит
		chrDisableReloadToLocation = false;
		Dialog.Text = "조심해, 조심! 어이쿠! 아, 너를 알겠어. 너는 "+GetFullName(PChar)+". 당신에 대해 많은 이야기를 들었습니다.";
		if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
		{
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("나는 선장이오 "+GetFullName(pchar)+".","나는 '의 선장이오"+PChar.Ship.Name+" 그리고 몇백 명의 진짜 악마들도 있지! 헤헤! 내 이름은 "+GetFullName(pchar)+".")+" 하지만 너는 기억나지 않아.",RandPhraseSimple("신사 여러분, 제 소개를 하겠습니다. 나는 선장입니다 "+GetFullName(pchar)+".","아직 서로 소개하지 않았군. 나는 '의 선장이오"+PChar.Ship.Name+" 깃발 아래에서 "+NationNameGenitive(sti(PChar.nation))+". 내 이름은 "+GetFullName(pchar)+".")+" 하지만 너는 기억나지 않아.");
//			link.l1 = "흠... 그런데 넌 누구지? 기억이 안 나는데.";
			link.l1.go = "Quest_1_Meeting";
		}
		else
		{
			link.l1 = "안녕, "+GetFullName(NPChar)+". 요즘 어때?";
			link.l1.go = "Quest_1_Work";
		}
		SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

	//=========== Первый квест ==========
	case "Quest_1_Meeting":
		sld = GetRealShip(sti(NPChar.Ship.Type));
		Dialog.Text = "나는 "+GetFullName(NPChar)+", 선장 "+xiStr(sld.BaseName+"Acc")+" "+NPChar.Ship.Name+NPCharRepPhrase(NPChar,". 스페인 본토 전체에서 가장 악명 높은 해적이오.",". 그냥 선원이야.");
		link.l1 = "그래, 이제 너를 기억하겠다.";
		link.l1.go = "Quest_1_Work";
		NPChar.meeting = true;
		break;

	case "Quest_1_Work":
		PChar.GenQuest.PGG_Quest.Template = rand(1);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
		{
			PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
		}
		PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar)+1;
		PChar.GenQuest.PGG_Quest.Nation = rand(NON_PIRATES);
		PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
		}
		PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
		while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
		{
			PChar.GenQuest.PGG_Quest.Island = GetRandIslandId();
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomShoreId(PChar.GenQuest.PGG_Quest.Island);
			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
			else
			{
				if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
			}
		}
		PChar.GenQuest.PGG_Quest.Island.Town = FindTownOnIsland(PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(pchar)].id, PChar.GenQuest.PGG_Quest.Island);
		PChar.GenQuest.PGG_Quest.Goods = GetRandomGood(FLAG_GOODS_TYPE_CROWN, FLAG_GOODS_NONE);
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "너와 볼 일이 있다, "+GetSexPhrase("동료","아가씨")+". 나는 그대라면 믿을 수 있다는 걸 알지만, 선술집에서는 도저히 이야기할 수가 없어 - 엿듣는 귀가 너무 많거든. 내 배에서 기다리고 있겠네. 내 낡은 배 이름은 '"+NPChar.Ship.Name+"'."";
//			link.l1 = "어서 말해, 난 손님 맞을 시간 없어.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("너와 네 칼잡이들에게 흥미로운 일이 있지.","힘을 합치면 정말 대단한 보물을 얻을지도 몰라! 물론 그 과정에서 누군가는 죽어야겠지. 헤헤."),RandPhraseSimple("선장님, 당신께 드릴 사업 제안이 있습니다.","선장님, 당신의 명성은 비할 데 없으니, 그래서 제가 아주 매혹적인 사업에 참여해 주시길 청하는 것입니다."))+RandPhraseSimple("우리 둘만 아는 얘기야. '의 사관실에서 이야기하자."+NPChar.Ship.Name+" 최고급 에일 통 앞에서. 오늘.","여기서 이야기하면 안 되니, 자세한 협상은 '에서 하자"+NPChar.Ship.Name+" 평온하게 지내게 해 주시오. 그리고 너무 오래 걸리지 말아 주시오.");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("이런 지체는 지옥에나 가라! 좋은 소식이면 당장 알고 싶고, 나쁜 소식이면 더더욱 바로 듣고 싶다!","이렇게 짧은 줄로는 소용없어! 선술집에 적당한 방이 있으니, 거기로 가자!"),RandPhraseSimple("그럼 왜 지금 바로, 선술집 방에서 당신의 제안을 논의할 수 없는 거지?","네 배에는 별로 가고 싶지 않다. 필요한 게 있으면 여기서 당장 말해!"));
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
			Dialog.Text = "쉿... 선술집에서는 사업 이야기를 하면 안 돼. 듣지 말아야 할 귀가 너무 많거든. 나는 내 배 '에서 기다리고 있네 "+NPChar.Ship.Name+". 그곳에서 이야기하자.";
			link.l1 = "나는 시간이 없고 방문하는 것도 싫어.";
		}
		link.l1.go = "Quest_1_Work_1";
		link.l2 = PCharRepPhrase(RandPhraseSimple("가겠다. 하지만 내 시간만 낭비하게 만들면, 네 혀를 뽑아버릴 거야!",RandSwear()+"좋아, 기다려. 네 제안이 그만한 가치가 있길 바란다. 그리고 나한테 장난칠 생각은 꿈도 꾸지 마!"),RandPhraseSimple("기꺼이 초대를 받아들이겠습니다, 선장님.","흥미롭군. 물론 가지."));
		link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

	case "Quest_1_Work_1":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("오, 멀미가 나는 거냐? 어서 가서 네 엄마 치마 밑에 숨어라!","겁먹었어?! 꺼져!"),RandPhraseSimple("안 돼. 금에 관심 없으면, 그건 네 선택이지.","이게 유일한 방법이야. 싫으면 말고, 다른 사람 plenty하게 있으니까."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("하! 너 용감하구나? 좋아, 내가 갈게!","보아하니 고집이 대단하군, 선장. 좋아, 나를 기다려."),RandPhraseSimple("좋아, 동의하지.","제법 말이 많군. 네 배에서 거래 이야기를 할 준비가 됐어."));
		link.l1.go = "Exit_Quest_1_AfterTavernTalk";
		link.l2 = PCharRepPhrase(RandPhraseSimple("하! 네가 나를 네 배로 유인해서 거기서 죽이려고 했지? 그건 안 통하지!","네 말은 한 푼 가치도 없어! 너랑은 거래 안 해!"),"의심스러운 제안이군. 거절해야겠어.");
		link.l2.go = "Quest_1_NotWork";
		break;

	case "Quest_1_NotWork":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("럼이나 가져와! 그리고 너는 내 눈앞에서 꺼져!","우리가 이미 모든 걸 다 이야기하지 않았나?"),RandPhraseSimple("네 일이나 해라. 나는 할 일이 있다.","우리 사이에 더 이야기할 게 없다고 생각해."));
		link.l1 = RandSwear();
		link.l1.go = "exit_2";
		break;

	case "Quest_1_Work_2":
		Dialog.Text = "내가 내 배에서 기다리고 있겠다고 말했잖아!";
		link.l1 = "오... 그래...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Quest_1_Work_2";
		break;

	case "Exit_Quest_1_AfterTavernTalk":
		PChar.GenQuest.PGG_Quest = 1;
		PChar.GenQuest.PGG_Quest.Stage = 0;
		PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
		Group_SetTaskNone("PGGQuest");

		SetTimerConditionParam("PGGQuest1_RemoveShip_Timer", "PGGQuest1_RemoveShip_Timer", 0, 0, 0, MakeInt(GetHour() + 6), false);
		PChar.Quest.PGGQuest1_RemoveShip_Timer.function = "PGG_Q1RemoveShip";

		NPChar.Ship.Mode = "Pirate";
		NPChar.DeckDialogNode = "Quest_1_Ship";
		NPChar.Nation.Bak = NPChar.Nation;
		NPChar.Nation = GetCityNation(GetCurrentTown());
		NPChar.AlwaysFriend = true;
		NPChar.Abordage.Enable = false; //нельзя брать на абордаж
		SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

		ReOpenQuestHeader("Gen_PGGQuest1");
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		}
		AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

		NextDiag.CurrentNode = "Quest_1_Work_2";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Ship":
		PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
		if (GetCompanionQuantity(PChar) == COMPANION_MAX)
		{
			Dialog.Text = RandPhraseSimple("오, 안 돼, 그건 곤란하지... 그거, 네게는 너무 많은 배 아닌가? "+GetSexPhrase("동료","아가씨")+"?","하! 이렇게 많은 사람들이 있는데 비밀을 지킬 수가 있겠어. 꺼져.");
			link.l1 = RandPhraseSimple("원하시는 대로 하겠습니다!","알겠어. 신경도 안 써.");
			link.l1.go = "Exit";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
			break;
		}
		PChar.GenQuest.PGG_Quest.Stage = 1;
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "좋아. 이제 불청객이 엿듣고 있지 않다는 걸 확신할 수 있겠군, 그리고 내 선원들도 이미 들었어. 그러니 내 제안은 주인 없는 물건을 좀 챙기자는 거야.";
//			link.l1 = "그게 뭐가 그렇게 어렵다고? 애초에 왜 나까지 필요하다는 거야?";
			Dialog.Text = RandPhraseSimple("어서 오십시오, 선장님!","좋아. 이제 불청객이 없는 게 확실하고, 내 선원들도 이미 다 들었지. 그래서 내 제안은, 주인 없는 물건을 좀 챙기자는 거야.")+" 내 제안은 주인 없는 물건을 좀 챙기자는 거야.";
			link.l1 = RandPhraseSimple("그게 뭐가 그렇게 어렵다고? 애초에 그런 일에 나를 왜 필요로 하는 거야?","주인도 없다니?! 농담하는 거지!");
		}
		else
		{
			Dialog.Text = "이제 주위에 듣지 말아야 할 귀는 없는 것 같으니, 어서 말해 봐!";
			link.l1 = "내 제안은 주인 없는 물건을 좀 챙기자는 거야.";
		}
		link.l1.go = "Quest_1_Ship_1";
		break;

	case "Quest_1_Ship_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = RandPhraseSimple("글쎄, 그걸 자기 것이라고 생각하는 사람들이 있어서, 그들에게 달리 설득해야 해.","물론 누군가는 죽어야겠지. 하지만 이게 문제될 건 없겠지?");
			link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("이제 본론으로 들어가자!","학살 냄새가 진동하는군! 그런데 그 자들은 어디 있지?"),RandPhraseSimple("당신의 제안에 대해 더 자세히 알고 싶소.","정확히 나한테 뭘 제안하는 거지?"));
			link.l1.go = "Quest_1_Ship_Detail";
			link.l2 = PCharRepPhrase(RandPhraseSimple("나를 속이려 드는군. 나는 그 짓에 끼지 않을 거야!","그건 쉬워 보이지만, 난 너를 믿지 않아! 네 대신 내가 위험을 감수하길 바라는 거냐? 난 못 하겠다!"),RandPhraseSimple("괜찮아 보이긴 하지만, 나는 사양할게.","아니, 나는 훔치지 않아. 차라리 선물로 주는 게 더 좋지."));
			link.l2.go = "Quest_1_Ship_Refuse";
		}
		else
		{
			Dialog.Text = "그게 뭐가 그렇게 어렵다고? 애초에 왜 나까지 필요하다는 거야?";
			link.l1 = "글쎄, 자기 것이라고 생각하는 사람들이 있어서, 그들에게 그렇지 않다는 걸 납득시켜야 해.";
			link.l1.go = "Quest_1_Ship_Detail";
		}
		break;

	case "Quest_1_Ship_Detail":
		sTmp = "A caravan belonging to " + NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)) + ", transporting ";
		if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
		{
			sTmp += "Slaves";
			PChar.GenQuest.PGG_Quest.Goods.Text = "Slaves";
		}
		else
		{
			sTmp += XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
			PChar.GenQuest.PGG_Quest.Goods.Text = XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name);
		}

		if (PChar.GenQuest.PGG_Quest.Island.Town == "" || PChar.GenQuest.PGG_Quest.Island.Town == "Caiman" ||
			PChar.GenQuest.PGG_Quest.Island.Town == "Terks" || PChar.GenQuest.PGG_Quest.Island.Town == "Dominica")
		{
			sLoc = GetIslandNameByID(PChar.GenQuest.PGG_Quest.Island);
		}
		else
		{
			sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
		}
		
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			sTmp +=	", stopped not far from " + sLoc + " at the cove of " + GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore) + " to resupply.";
		}
		else
		{
			sTmp += ", was caught in the storm not far from " + sLoc + " and went down. But they managed to secure part of the cargo and landed in the cove of " + GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore) +
				" Now they are waiting their squadron to come.";
		}
		
		Dialog.Text = sTmp;
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("질질 끌지 말고, 빨리 말해!","내가 너에 대해 맞게 봤군, 또 뭘 알고 있지?"),RandPhraseSimple("그거 정말 흥미롭군요, 계속 말씀해 주세요!","나는 "+GetSexPhrase("전부","모두")+" 귀!"));
		link.l1.go = "Quest_1_Ship_Detail_1";

		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			link.l2 = PCharRepPhrase(RandPhraseSimple("그거 꽤나 솔깃한 제안이긴 하지만, 그래도 거절하겠소. 나는 굳이 다투고 싶지 않으니 "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+".","대상단이라고? 주인도 없다니?! 병사 천 명쯤은 지키고 있어야 하는 거 아니야! 아니, 이건 안 되겠어. 난 간다."),RandPhraseSimple("아니, 나는 ~와 전쟁 중이 아니오 "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+", 그래서 난 관심 없어.","내 대답은 아니오! 나는 내 관계를 망칠 생각이 없어! "+NationNameAblative(sti(PChar.GenQuest.PGG_Quest.Nation))+"!"));
			link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
		}
		else
		{
			Dialog.Text = "학살 냄새가 진동하는군! 자세한 내용은 어때?";
			link.l1 = sTmp;
		}
		if (sti(PChar.GenQuest.PGG_Quest.Template)) 
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
		}
		AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
		AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text));
		AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
		AddQuestUserData("Gen_PGGQuest1", "sShore", GetLocationNameByID(PChar.GenQuest.PGG_Quest.Island.Shore));
		break;

	case "Quest_1_Ship_Detail_1":
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
//			Dialog.Text = "우리에겐 오직 "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" 그들을 가로막으려고.";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("In "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" 대상단이 너무 멀리 가버리면, 우리는 따라잡을 수 없을 거야.","우리에겐 정확히 "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" 놈들을 전부 죽이고 전리품을 챙길 날이 얼마 안 남았어!"),RandPhraseSimple("우리에겐 오직 "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" 우리에게 주어진 전체 작전을 위한 날들이다.","서둘러야 해. "+PChar.Name+". 우리에게 남은 것은 "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+"."));
			link.l1 = RandPhraseSimple("제때 해낼 거야! 오늘 출항하자.","그럼 시간 낭비하지 말자. 오늘 출항하라고 명령 내려.");
			link.l1.go = "Exit_Quest_1_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
		}
		else
		{
			Dialog.Text = "그거 참 흥미롭군요, 계속 말씀해 주십시오.";
			link.l1 = "우리에겐 오직 "+FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days))+" 그들을 가로막으려고.";
			link.l1.go = "Quest_1_Ship_Accept";
			AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
		}
		AddQuestUserData("Gen_PGGQuest1", "nDays", FindRussianDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

	case "Quest_1_Ship_Accept":
		Dialog.Text = "시간 낭비하지 말자! 어서 가자!";
		link.l1 = "자, 가자!";
		link.l1.go = "Exit_Quest_1_Accept";
		break;

	case "Exit_Quest_1_Accept":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
		{
			PChar.GenQuest.PGG_Quest.Stage = 2;
			PGG_Q1RemoveShip("");

			if (sti(PChar.GenQuest.PGG_Quest.Template)) 
			{
				PGG_Q1PlaceShipsNearIsland();
			}
			else
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
				PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
				PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
			}
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
			PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
			PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

			SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
			PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

			NPChar.PGGAi.IsPGG = false;
			NPChar.PGGAi.location.town = "none";
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");
			DeleteAttribute(NPChar, "AlwaysFriend");

			SetCompanionIndex(PChar, -1, sti(NPChar.index));
			SetCharacterRemovable(NPChar, false);
			
			SetBaseShipData(NPChar);
            DeleteAttribute(NPChar,"ship.sails");
			DeleteAttribute(NPChar,"ship.masts");
			DeleteAttribute(NPChar,"ship.blots");
			DeleteAttribute(NPChar,"ship.hulls");
			
			Fantom_SetCannons(NPChar, "pirate");
			Fantom_SetBalls(NPChar, "pirate");
		}
		NextDiag.CurrentNode = "Quest_1_Ship_Accept";
		DialogExit();
		break;

	case "Quest_1_Ship_Refuse":
		Dialog.Text = RandSwear()+"넌 나를 실망시켰어, 선장. 내가 너를 초대할 거라고 생각했나? "+RandPhraseSimple("주일 미사?!!","애들 장난이냐!??"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("그건 네 일이지. 그리고 결정은 내가 한다.","나는 푼돈 몇 푼 때문에 목매달릴 생각 없어."),RandPhraseSimple("내 결정은 최종이오, 선장.","더 이상 논의할 것이 없다."));
		link.l1.go = "Exit_Quest_1_Refuse";
		break;

	case "Exit_Quest_1_Refuse":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

			AddQuestRecord("Gen_PGGQuest1", "q1_Close");
			AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Gen_PGGQuest1");
			DeleteAttribute(NPChar, "AlwaysFriend");
		}
		NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
		NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
		DialogExit();
		break;

	case "Quest_1_Ship_BadWay":
		Dialog.Text = PCharRepPhrase("아, 좀! 다 순조롭게 진행될 거야, 아무도 모를 거라고. 모두 죽여버리면 되잖아."),RandPhraseSimple("어디로 가는 거요, 선장? 혹시 관청에 가는 건가?","호랑이 굴에 쉽게 나올 수 있다고 생각하며 들어가는 건 정말 어리석은 짓이지."));
		link.l1 = PCharRepPhrase(RandSwear()+RandPhraseSimple("바다 악마나 뽀뽀해라! 내가 선장이야 "+GetFullName(PChar)+" 나는 너 따위 신경 안 써! 나 간다!","악마에게 맹세코, 너 정말 나를 미치게 만드는구나!"),RandPhraseSimple("당신의 제안에는 전혀 관심이 없소, 더 이상 우리 사이에 할 말도 없구려. 안녕히 가시오.","우리 사이에 더 이상 논의할 것은 없다고 생각하오. 미안하오, 나는 바빠서 가야 하오."));
		link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

	case "Quest_1_Ship_BadWay_1":
		Dialog.Text = RandSwear()+PCharRepPhrase(RandPhraseSimple("Seize "+GetSexPhrase("그를","그녀")+"! 무승부 "+GetSexPhrase("그를","그녀")+" 대포 앞으로! 어떤 깃발 색인지 보자 "+GetSexPhrase("그의","그녀")+" 내장이야!!!","이봐! 조니! 헨더슨! 저거 잡아! "+GetSexPhrase("악당","아가씨")+"! 놓치지 마 "+GetSexPhrase("그를","그녀")+" 구명보트로 가자!!!"),RandPhraseSimple("안됐군요, 선장님! 그래도 우리 선창이 마음에 들었으면 좋겠소. 그 다음에 당신을 어떻게 할지 결정하겠소.","백인 노예들은 오래 못 산다고 알려져 있소, 선장. 그러니 선택하시오: 헨즈가 네 머리에 총을 쏘든지, 아니면 평생 채석장에서 살든지."));
		link.l1 = PCharRepPhrase(RandPhraseSimple("네 더러운 내장을 씹게 해주마, "+GetFullName(NPChar)+"!!!","비켜라! 이 악당들아! 여기서 바로 죽여주마!"),RandPhraseSimple("네 제안은 받아들일 수 없어... 그리고 정말 어리석군!!!","보아하니 너희는 그다지 환대하지 않는군... 비켜라!!!"));
		link.l1.go = "Exit_Quest_1_DeckFight";
		break;

	case "Exit_Quest_1_DeckFight":
        GetCharacterPos(NPChar, &locx, &locy, &locz);
		DeleteAttribute(NPChar, "AlwaysFriend");
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		LAi_SetImmortal(NPChar, true);
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		//группа может быть занята, а проверок по группам у нас нет... :(
		if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
		{
			sTmp = "PGGTmp";
		}
		else
		{
			sTmp = "PGGQst";
		}
		PChar.GenQuest.PGG_Quest.GrpID = sTmp;

		for (i=1; i<5; i++)
		{
			sld = CharacterFromID("saylor_0" + i);
			LAi_group_MoveCharacter(sld, sTmp);
		}
		LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
		LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
		chrDisableReloadToLocation = true;

		PGG_ChangeRelation2MainCharacter(NPChar, -20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetFightMode(pchar, true);
		break;

	case "Quest_1_Time2Late":
		chrDisableReloadToLocation = false;

		//перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
		PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
		PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
		PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

//		Dialog.Text = "그래, "+GetFullName(PChar)+", 너랑 엮인 게 실수였다는 걸 알겠군. 이제 우리에겐 전리품도 없어. 잘 가라!";
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("젠장! 우리가 늦었잖아 – 다 저 멍청한 게으름뱅이들 때문이야! 이제 너랑 나눌 전리품도 없어, "+GetFullName(PChar)+"돛 올려! 여기서 나가자! ","그래, "+GetFullName(PChar)+", 너랑 엮인 게 실수였다는 걸 알겠군. 이제 우리한텐 전리품도 없어. 잘 가라!"),RandPhraseSimple("그들은 사라졌어 – 다 네가 늦게 온 탓이야! 이제 우리는 각자의 길을 가는 거다, "+GetFullName(PChar)+".","이제 우리가 그 대상단을 따라잡을 방법은 없어. 너랑 엮인 게 내 실수였지. 잘 가라!"))link.l1 = PCharRepPhrase(RandPhraseSimple("그런 대상단은 집어치워! 진주 채취꾼이 훨씬 낫지, 위험도 없고!","운이 우리 편이니 내일은 또 다른 날이야! 바다에는 우리가 돈을 빼앗아 줄 불쌍한 상인들이 널렸지!"),RandPhraseSimple("정말 안타깝군, 이렇게 훌륭한 작전이 완전히 실패로 끝나다니! 작별이오!","사람이 계획하고 신이 결정한다지... 잘 가라!"));
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;

			LAi_SetWarriorTypeNoGroup(NPChar);
			LAi_group_MoveCharacter(NPChar, "GroupDeck");

			PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
			if (PChar.location == "Ship_deck")
			{
/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
*/				PChar.quest.Munity = "Deads";
			}
			PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
		}
		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		break;

	case "Quest_1_CheckResult":
		if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
		{
			Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
		}
		else
		{
			PChar.quest.Munity = "Deads";
		}
		chrDisableReloadToLocation = false;

		//не взяли груз...
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days)*10000;
//			Dialog.Text = "아, 도대체 왜 너랑 엮여서 이 지경이 된 거지. 네가 모든 걸 망쳐놨어. 이제 네가 내게 벌금을 내야 한다. "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+".";
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("Bloodthirsty "+GetSexPhrase("놈","오물")+"! 모든 게 죄다 바다 악마한테로 곧장 가버렸어!"+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" 페소를 당장 내놓고, 내 눈앞에서 꺼져!","네가 네 자신을 넬슨 제독이라도 된다고 생각하나? 전리품을 다 침몰시켰군, "+GetSexPhrase("멍청이","어리석은 여자")+"! 지금 내놔 "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" 페소나 챙기고 꺼져!"),RandPhraseSimple("여기서 전쟁이라도 벌이겠다는 건가! 그건 도저히 용납할 수 없어! 하지만, 돈을 내면 잊어줄 수도 있지\n "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" 페소입니다.","네 방법은 완전히 용납할 수 없어! 네가 모든 일을 망쳐놨잖아! 당장 우리 몫을 내놔, 그 액수는 "+FindRussianMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))+" 페소를 가지고 원하는 곳으로 가라!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("나 아니었으면 지금쯤 게밥이 됐을 거다, 이 욕심 많은 놈아!","그래, 내가 그놈들 기함이 네 배에 올라타게 놔뒀어야 했어. 그랬다면 지금쯤 넌 돛대에 매달려 공기나 더럽히지 않았을 텐데!"),RandPhraseSimple("네 요구는 도가 지나치고, 네 암시는 모욕적이야!","우리는 벌금에 대해 합의한 적 없으니, 나는 너한테 아무것도 안 내!"));
			link.l1.go = "Quest_1_NotPay";
			if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
			{
				link.l2 = PCharRepPhrase(RandPhraseSimple("지금은 너랑 싸울 수 없어, 너도 알잖아! 네 페소나 목에 걸려라!"," 페소?!! 오늘은 정말 운이 없구만. 나도 동의해."),RandPhraseSimple("네 요구는 터무니없지만, 어쩔 수 없는 것 같군.","너희들 식욕이 지나치긴 하지만, 나도 동의할 수밖에 없군!"));
				link.l2.go = "Exit_Quest_1_Failed";
			}
		}
		else
		{
			PChar.GenQuest.PGG_Quest.Stage = -1;
			Dialog.Text = "아, 도대체 왜 너랑 엮여서 이 꼴이 된 거지. 네가 다 망쳐 놨어.";
			link.l1 = "아, 제발! 너도 직접 봤잖아, 다른 방법은 없었다는 걸.";
			link.l1.go = "Exit_Quest_1_Failed";
		}

		//минимум треть если взял, то гуд!
		if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty)/3))
		{
			PChar.GenQuest.PGG_Quest.Ok = 1;
//			Dialog.Text = "그러니까, 우리의 전리품은 "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+". 나누자.";
			Dialog.Text = PCharRepPhrase("좋은 거래였어! 그러니까, 우리의 전리품은 "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","훌륭한 일입니다, 선장님! 우리의 전리품이 "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");
			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = Dialog.Text+PCharRepPhrase(" 내 몫은 "," 내 배의 몫 - ");
			}
			else
			{
				Dialog.Text = Dialog.Text+" 네 몫은 ";
			}
			Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
			link.l1 = PCharRepPhrase(RandPhraseSimple("모든 게 맞습니다! 보트는 이미 실리고 있습니다!","그래, 모두 맞아. 약속은 약속이지."),RandPhraseSimple("당신의 계산이 맞소. 나도 동의하오.","나눌 때만큼은 너한테 흠잡을 데가 없어."));
			link.l1.go = "Exit_Quest_1_End";
			link.l2 = PCharRepPhrase(RandPhraseSimple("네 몫을 달라고 감히 요구해? 당장 돛대에 매달아야 마땅하겠다!","네 몫? 여기선 각자도생이야. 남은 게 없으면, 그건 네 문제지!"),RandPhraseSimple("네가 몫을 기대할 수 있을 것 같진 않은데.","내 대답은 아니야! 너 같은 악당들과는 절대 나누지 않겠다!"));
			link.l2.go = "Quest_1_NotPay";
		}
		else
		{
			AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
		}
		break;

	case "Quest_1_NotPay":
		Dialog.Text = PCharRepPhrase(RandPhraseSimple("그래, 알겠다. 더 이상 따지지 않을게! 잘 가라!","피를 흘려서 일을 더 악화시키지 말자! 다음번엔 운이 더 좋을 거야!"),RandPhraseSimple("음, 그럼 이만, 선장님. 나는 요구할 처지가 아니오...","내 배의 손실과 피해 때문에 정당한 결정을 고집할 수 없소. 양심에 맡기겠소, 선장!"));
		link.l1 = PCharRepPhrase(RandPhraseSimple("순풍이 불길 바라오!","용골 아래 7피트다!"),RandPhraseSimple("안녕히 가시오! 신선한 바닷바람이 당신께 도움이 되길 바라오!","우리의 불운이 당신을 더 괴팍하게 만들지 않길 바라오, 선장! 잘 가시오!"));
		link.l1.go = "Exit_Quest_1_Failed";
		PChar.GenQuest.PGG_Quest.Stage = -1;

		bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
		if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
		{
			PChar.GenQuest.PGG_Quest.Stage = 4;
			Dialog.Text = PCharRepPhrase(RandPhraseSimple("못 알아들었냐! 목숨을 돈 주고 살 수 있었을 텐데! 저 자식 잡아라!","아니면 우리가 너랑 장난이라도 치는 줄 아냐? 좋아, 한 번 밑창에 끌어내리면 좀 더 말을 잘 듣게 되겠지!"),RandPhraseSimple("그럼 네 목숨을 좀 줄여줘야겠군, 선장! 좋게 갈 생각이 없다면, 곧 성 마르틴을 만나게 될 거다!","나에게 선택의 여지가 없군, "+GetFullName(PChar)+"! 네가 좋아하든 말든 내 것은 내가 가져가겠다!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("악마에게 맹세코, 네놈 이 일에 반드시 대가를 치르게 될 거다!!!","요호! 그럼 가서 날 데려와 봐, 선장. "+GetFullName(PChar)+"! "),RandPhraseSimple("상처가 길고 깊게 날 거다!","빨리 죽고 싶어, 아니면 좀 고통스럽게 죽고 싶어?"));
			link.l1.go = "Exit_Quest_1_FailedFight";
		}
		break;

	case "Exit_Quest_1_Failed":
		if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
		{
			AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
			AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
		AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("",""));
		AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("",""));
		}
		CloseQuestHeader("Gen_PGGQuest1");
		RemoveCharacterCompanion(pchar, NPChar);

		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
		}
		else
		{
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
		}
		PGG_ChangeRelation2MainCharacter(NPChar, -5);

		LAi_SetImmortal(NPChar, true);
		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		NextDiag.CurrentNode = "Quest_1_Failed";
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

	case "Quest_1_Failed":
		Dialog.Text = "이제 너랑 더 이상 엮이고 싶지 않아!";
		link.l1 = "전혀 문제없어.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_Failed";
		break;

	case "Quest_1_End":
		Dialog.Text = "거래하게 되어 반가웠소. 행운을 빌겠소.";
		link.l1 = "당신도 마찬가지요.";
		link.l1.go = "Exit";
		NextDiag.TempNode = "Quest_1_End";
		break;

	case "Exit_Quest_1_FailedFight":
		RemoveCharacterCompanion(pchar, NPChar);

		LAi_LockFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);	
		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");
	
		PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
		chrDisableReloadToLocation = true;

		Group_AddCharacter("PGGQuest", NPChar.id);
		Group_SetGroupCommander("PGGQuest", NPChar.id);
		Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
		Group_SetTaskNone("PGGQuest");

		PGG_ChangeRelation2MainCharacter(NPChar, -15);

		GetCharacterPos(NPChar, &locx, &locy, &locz);
        sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
		NextDiag.CurrentNode = "Second Time";
		DialogExit();

		Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
		NPChar.location = PChar.location;
		if (PChar.location != "Ship_Deck") sTmp = "reload1_back";

		PChar.questTemp.Chr2Remove = NPChar.id;
		LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", 5.0);

		LAi_SetImmortal(NPChar, true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_Quest_1_End":
		RemoveCharacterCompanion(PChar, NPChar);

		i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
		i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
		n = GetCompanionQuantity(PChar);
		SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
		for (i = 1; i < n; i++)
		{
			iRnd = GetCompanionIndex(PChar, i);
			if (iRnd != -1)
			{
				sld = GetCharacter(iRnd);
				if (GetRemovable(sld))
				{
					Log_TestInfo("" + sld.id);
					SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
				}
			}
		}
*/
		RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
/*		if (PChar.Location == "Ship_deck")
		{
			PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
			PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
		}
		else
		{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
		//}
		AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
		CloseQuestHeader("Gen_PGGQuest1");

		//что б не били сопровождение.
		for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
		{
			sld = CharacterFromID("pirate_" + i);
			LAi_SetImmortal(sld, true);
		}

		LAi_SetImmortal(NPChar, true);
		NextDiag.CurrentNode = "Quest_1_End";
		DialogExit();
  		LAi_SetWarriorType(NPChar); // сброс группы ГГ
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

	case "Quest_1_SharePrise":
		chrDisableReloadToLocation = false;
		Dialog.Text = PCharRepPhrase("진짜 학살이었지! 같이 있던 계집애들이 없어서 아쉽군! 그래도 전리품이 그걸 만회해주네  "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".","나쁘지 않군, 선장! 전리품이 보상해주지 "+PChar.GenQuest.PGG_Quest.Goods.Taken+" "+PChar.GenQuest.PGG_Quest.Goods.Text+".");

		i = sti(PChar.GenQuest.PGG_Quest.Parts);
		PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
        SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
		if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
		{
			Dialog.Text = Dialog.Text+" 내 몫은 ";
		}
		else
		{
			Dialog.Text = Dialog.Text+" 네 몫은 ";
		}
		Dialog.Text = Dialog.Text+PChar.GenQuest.PGG_Quest.Goods.Part+".";
		link.l1 = PCharRepPhrase(RandPhraseSimple("완전히 공정하잖아, 젠장!","모든 게 완벽하게 괜찮아, 젠장할!"),RandPhraseSimple("당신의 계산이 맞소. 나도 동의하오.","나눌 때만큼은 너한테 흠잡을 데가 없어."));
		link.l1.go = "Exit_Quest_1_End";
		break;
//===================================
//              Exits 
//===================================
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;
		
	case "Exit_2":
		if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;		

	case "Exit_Smugglers_Fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();

		LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
		LAi_SetFightMode(pchar, true);
		break;

	case "Exit_ShowParam":
		NextDiag.CurrentNode = "Second Time";
//		NPChar.quest.meeting = true;
		DialogExit();

		PChar.SystemInfo.OnlyShowCharacter = true;
		LaunchCharacter(NPChar);
		break;
	}
}
/* TEMPLATE
		Dialog.Text = "";
		link.l1 = "";
		link.l1.go = "";
		link.l2 = "";
		link.l2.go = "";
		link.l3 = "";
		link.l3.go = "";
*/
