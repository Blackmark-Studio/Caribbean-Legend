void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Have you heard? The local robber " + GetFullName(npchar) + " found a new victim. One captain got scared and bought off. They say, he gave him " + FindRussianMoneyString(iMoney) + ", he-he... ", 
				"Yeah, captain " + GetFullName(pchar) + ", I already heard that you had to pay " + FindRussianMoneyString(iMoney) + ", to buy off a local bandit, " + GetFullName(npchar) + ". Now that's what I call bad luck! Ha-ha-ha!", 
				"Have you heard that the local bandits attacked one captain? He was totally robbed, he lost " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Have you heard? That bandit " + GetFullName(npchar) + " has finally found justice. He and his boys tried to rob "+ GetSexPhrase("some captain, but he turned out to be","some lady captain, but she turned out to be") +" a tough nut. So our dear robber shited his pants, ha-ha! That will be a lesson for him! Robbing the local farmers is one thing, but a brave captain is a different story!", 
				"Thank you, captain " + GetFullName(pchar) + ", for finally dealing with the gang of that bandit " + GetFullName(npchar) + ". Those rascals were really a pain in everyone's ass. We were scared to even send couriers to the farm for milk, they could have intercepted them and rob of all the money."), 
				"Have you heard, "+ GetSexPhrase("finally, some captain","finally, some lady captain") +" stopped that rascal " + GetFullName(npchar) + ", who was in 'charge' of the jungle, terrorizing all the local farmers. I do hope, it will stop them from their dirty deeds for long enough...", 
				"Have you heard that local bandit " + GetFullName(npchar) + " and his boys attempted to rob "+ GetSexPhrase("some captain","some lady captain") +"? Bah! Nothing of the sort! That captain turned out to be a tough nut. They say, he chased on these robbers over all the jungle like a shark chases flock of sardines. Thank God that there are still people who can stand up for us at time when the authorities do nothing, too busy with their dark deeds..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("거기 멈춰서 무기 내려놔! 돈 내놓든가, 아니면 목숨 내놔!","거기 가만히 있어, "+GetSexPhrase("여행자","아가씨")+"!) 무기에 손대지 말고, 갑작스러운 행동도 하지 마!","거기 가만히 있어라, "+GetSexPhrase("여행자","아가씨")+"! 여기는 통행료를 내야 지나갈 수 있는 길이다. 지나가고 싶으면 통행료를 내."),LinkRandPhrase("이봐, "+GetSexPhrase("동료","아가씨")+"! 그렇게 서두르지 마! 네 돈주머니가 얼마나 무거운지 좀 보자.","가까이 와줄래, 친구? 네 주머니에서 금화 소리가 나는지 듣고 싶군.","잠깐만, "+GetSexPhrase("동료","아가씨")+". 우리 녀석들이랑 나는 네 주머니에 금이 얼마나 들어갈지 내기를 했지. 이제 일이 험악해지기 전에 확인해야겠다."),"서두르지 마, "+GetSexPhrase("여행자","여보")+"! 우리 진솔하게 이야기 좀 해볼까?");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("왜 그런 헛소리를 하는 거야?","무슨 일이야?","무슨 소리야?"),"무슨 뜻이야?","도대체 무슨 뜻이야?");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("도적놈들?! 잘 됐군, 한판 붙고 싶었어!","오, 너희는 도적들이구나! 법망을 피해 숨고 있었던 거지? 그래, 이제 정의가 너희를 찾아온 것 같군...","남을 괴롭히는 게 무례하다는 걸 아직도 못 배웠나? 내가 직접 가르쳐줘야겠군..."),LinkRandPhrase("오, 너 제법 건방지구나?! 네 혀만큼 칼도 날카롭길 바란다.","네가 말재주가 뛰어난 건 알겠군. 칼도 그만큼 잘 다루길 바란다.","오, 도적놈들! 너희 같은 놈들이 그렇게 많이 교수대에 매달렸는데도, 아직도 스스로 교수대로 걸어가는 걸 멈추질 못하는구나."),LinkRandPhrase(RandPhraseSimple("이런, 도적놈들! 너희 같은 놈들에게는 원래 말도 아깝다!","뭐 이런 건방진 놈이 다 있나! 똥더미처럼 구린내가 진동하는 주제에 감히 점잖은\n "+GetSexPhrase("놈","소녀")+"."),"너랑 말장난할 생각 없어. 내 권총이 말 대신 해줄 테니!","또 도적들이군! 음, 교수대는 약속 못 하겠지만, 네 배에 구멍 두어 개쯤은 확실히 내줄 수 있지!"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("그리고 순찰대가 나를 바짝 따라오고 있다는 거 알고 있나? 내가 휘파람만 불면 너는 끝장이야.",RandPhraseSimple("있지, 내가 순찰대를 부를 수도 있어. 그게 두렵지 않나? 바로 근처에 있어. 아마 널 찾고 있을 거야.","최근에 너를 찾으려고 순찰대가 파견됐어, 언제든 도착할 수 있어. 지금 엄청 위험한 짓을 하고 있는 거야."),RandPhraseSimple("최대한 빨리 도망치는 게 좋겠어. 순찰대가 이쪽으로 오고 있어; 방금 그들의 장교와 얘기했거든.","우리 대화를 계속하고 싶지만, 방금 만난 순찰대가 우리 사이가 가까운 친구로 발전하는 걸 허락하지 않을 것 같군."));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("바보짓 하지 마! 돈을 바로 내놔, 그래야 널 보내줄지도 몰라!","여행 통행료에 대해 못 들었나? 금을 내놓지 않으면 목숨을 내놓게 될 거다!","헤헷, 이 작은 모험이 너한테 돈 좀 들겠군... 내가 화내지 않는다면 말이지."),RandPhraseSimple("아주 간단해. 네가 가진 금을 전부 내놓으면 자유롭게 떠날 수 있지. 아니면 여기 남아서 우리가 어차피 네 금을 다 가져가게 될 거야. 하지만 두 번째 선택은 네가 원하지 않을 것 같은데, 헤헤.","모르는 척하지 마! 네가 죽어서 내가 직접 가져가길 원하지 않으면, 돈주머니 내놔!"),"느려터졌으니 내가 설명해 주지. 목숨이 아깝다면 가진 돈 전부 내놔.");
			Link.l1 = "젠장, 이 망할 놈아! 난 겨우 "+makeint(makeint(Pchar.money)/20)*10+" 페소입니다.";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("내 돈을 원해? 와서 가져가 봐, 네가 얼마나 값어치 있는지 직접 보겠어!","감히 이런 무례를! 예의를 제대로 가르쳐 주마!","참 자신감이군! 좋아, 진짜를 상대로 네가 어떻게 하는지 보자고\n "+GetSexPhrase("바다늑대","루브 데 메르")+"!"),LinkRandPhrase("이런 무례함에는 채찍질을 받아야 마땅하오!","이 악당들아! 지옥에서 따뜻한 자리를 위해 네 놈들 악마에게나 빌어라!","너희 같은 교수대의 새끼들은 진작에 목매달렸어야 했지! 좋아, 내 검을 너희 피로 물들여야겠군!"),RandPhraseSimple("내가 왜 너한테 내 돈을 줘야 한다고 생각하지?","그리고 내가 무장한 채로 여기 산책하러 온 게 아니라는 걸 눈치채지 못했나?"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("젠장! 좋아, 나가도 된다. 하지만 여기 있는 동안 소리라도 낼 생각은 하지 마라!","이번엔 운이 좋았지만, 다음번엔 두 배로 갚아야 할 거야! 잊지 말고 우리한테 꼭 상기시켜, 헤헤.");
				Link.l1 = RandPhraseSimple("물론이지.","지금이라도 도망쳐, 아직 기회가 있을 때.");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("조용히 죽여주지. 비명 한 번 못 지를 거다.","젠장! 네가 경보를 울리기 전에 빨리 죽여야겠군.");
					Link.l1 = "그래, 이건 네 장례식이야. 내가 경고했지.";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("내가 네 순찰대에 왜 신경 써야 하지? 내가 걔네들한테 돈 주고 있거든. 그러니까 지갑이나 내놓고 입 다물어.","나를 겁줄 수 있다고 생각해? 이 정글에서 너 같은 놈들을 단속하는 게 바로 나다. 지금까지 아무도 대가를 치르지 않고 나간 적 없어!");
					Link.l1 = "젠장, 이 악당아! 난 겨우 "+makeint(makeint(Pchar.money)/20)*10+" 페소입니다.";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("헤, 너 같은 약골한테 명령 따위 안 들어.","그런 건방짐에는 네 두개골에 구멍 두 개 더 뚫어주겠다! 네 머리 좀 환기시켜 줄 겸.","이런 무례함은 그냥 넘어가지 않을 것이다!"),"그렇게 하지 말았어야지...");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
		    bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("이봐, 그렇게 흥분하지 마, "+GetSexPhrase("동료","아가씨")+"! 그냥 농담이었어! 가던 길 가도 돼!","좋아, 마음을 바꿨다. 그렇게 대단하다면 가도 된다."),"뭐야, 한 "+GetSexPhrase("'용감한 선장'","'호전적인 아가씨'")+"또? 알겠어, 평안히 가...","진정해, "+GetSexPhrase("동료","아가씨")+". 있잖아, 우리가 착각했어, "+GetSexPhrase(" 우리는 네가 상인인 줄 알았어"," 우리는 네가 상인인 줄 알았어")+". 가도 된다.");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("좋아, 다시 만날 때까지 안녕!","아직 그만둘 수 있을 때 사람들 약탈하는 짓 그만둬라.","좋아, 하지만 다시 만나기만 해 봐..."),RandPhraseSimple("다음에는 네가 누구를 협박하는지 잘 알아둬라, 이 쓸모없는 놈아.","오늘은 기분이 좋아서 다행이군."),RandPhraseSimple("이 범죄적인 장사는 결국 너를 죽음으로 이끌 거다. 잘 가라.","현명한 결정이군. 자, 행운을 빌어!"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("아니, 친구야. 이제 내가 예의가 뭔지 제대로 가르쳐주지!","오, 겁먹었나? 뭐, 자기가 한 짓에는 책임을 져야지, 안 그래?","아니야! 네놈을 산 채로 가죽 벗기기 전엔 절대 진정 못 해!");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("너도 평화롭게 갈 수 있었을 텐데! 이제 네 잘못이니 누구 탓도 하지 마라!","네가 먼저 시작하지 말았어야지, 이 악당아! 이제 넌 개처럼 죽게 될 거다!","아, 좋아! 널 갈기갈기 찢어주마! 네 간을 도려내서 개들한테 먹이로 줄 거야!");
				Link.l1 = RandPhraseSimple("네 말 그대로 목구멍에 처넣어 주마!","누구를 협박하는 거냐, 이 쓰레기 놈아?!");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("좋아! 내놔, 그리고 꺼져!","별건 아니지만, 없는 것보단 낫지. 똑똑한 사람과 거래하니 좋군! 이제 가도 된다."),"그건 또 다른 이야기지! 내 친구가 늘 그러더군, '똑똑한 사람 말을 듣는 것도 좋지만, 바보랑 얘기하는 게 훨씬 재밌다'고! 헤헤!","네 금을 받는 대신 충고 하나 해주지. 정글에서는 절대 돌아다니지 마라, 만약 네가\n "+GetSexPhrase("겁쟁이 같으니. 술집에서 럼주나 마셔, 그래야 너도 네 돈주머니도 안전할 테니까!","아가씨라면, 도둑맞은 게 그나마 다행일 수도 있지.")+".");
				Link.l1 = "젠장할 놈!";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "네가 나를 속이려는 거지! 걱정 마, 내 칼로 간지럽혀 줄 테니까, 뭐라도 떨어지겠지.";
				Link.l1 = "젠장!";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("또 왔어? 내가 화내기 전에 얼른 집에 가서 엄마한테나 가!","뭐야? 아직도 네 금을 다 안 줬다고? 하하!","봐, "+GetSexPhrase("동료","아가씨")+", 너 정말 지긋지긋해! 아직 살아 있을 때 내 눈앞에서 꺼져!");
			Link.l1 = "그래, 나 벌써 간다.";
			Link.l1.go = "Exit";
			Link.l2 = "공평하지 않을 것 같았어. 그래서 바로잡기로 결심했지...";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("더 필요한 게 뭐야? 이미 네가 떠나기로 했잖아!","날 내버려 둬, "+GetSexPhrase("녀석","아가씨")+". 나는 내 일만 신경 쓰고, 너도 네 일이나 해. 우리 서로 잘 지내려고 애쓸 필요 없어!","지금 나가. "+GetSexPhrase("동료","아가씨")+"이런 젠장, 정말 네 돈 전부 다 내줄 생각이냐?");
			Link.l1 = "그래, 나 벌써 간다.";
			Link.l1.go = "Exit";
			Link.l2 = "작별 인사를 하지 않았던 게 생각났어! 그러니 제대로 작별 인사를 하자꾸나...";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("날 내버려 둬! 도와줘! 살고 싶어!","도와줘! "+GetSexPhrase("그는 미치광이야","그녀는 미치광이야")+"! 죽이지 마!","살려줘! 난 그냥 보잘것없는 도적일 뿐이야! 난 죽기엔 아직 너무 젊어!");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("집에만 있었더라면, 지금쯤 살아 있었을 텐데!","그전에 생각했어야지!","항상 결과가 따른다는 걸 알았어야지!"),"조만간 이런 일이 일어날 수밖에 없었지.","이제 와서 후회해도 늦었으니, 싸워라, 이 쓰레기놈들아!");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
