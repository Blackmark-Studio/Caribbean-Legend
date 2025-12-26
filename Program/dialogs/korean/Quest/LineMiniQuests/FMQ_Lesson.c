// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "명백한 버그다. 개발자들에게 알려라.";
			link.l1 = "그래, 그렇게 할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "오, "+GetFullName(pchar)+"! 친구, 너 좀 달라 보이는데다 성공도 했구나! 이제 너에 대한 소문이 돌기 시작했어, 알지? 배우는 것도 빠르구나, 나리, 내가 정말 자랑스럽다. 앞으로도 더 큰 행운과 복이 있기를 바란다! 다시 만나서 반갑구나!";
				link.l1 = "그레구아르 발리니 나리, 이런 만남이 있군요! 제 보잘것없는 성취에 대해 많은 빚을 졌습니다. 저도 만나서 반갑습니다! 행운을 빕니다!";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "오, "+GetFullName(pchar)+"! 친구, 예전과는 다르게 보이네, 그리고 성공도 했구나! 이제 너에 대한 소문이 돌기 시작했어, 알지? 정말 빨리 배우는구나, 나리, 자네가 자랑스럽네.";
				link.l1 = "Gregoire Valinnie 나리, 이런 만남이 다 있군요! 제 보잘것없는 성취에 큰 빚을 졌습니다. 만나서 반갑습니다! 맞춰볼까요, 저에게 사업 제안이 있으신가요?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "그래! 그렇다네. 간단히 말하지, 시간은 돈이니까. 그러니까, 브라질에서 퀴라소로 전략적으로 중요한 화물을 싣고 가던 네덜란드 왕립 함대가 트리니다드와 본토 사이에서 영국군의 기습을 받았어. 회사 소속 플라이트 한 척만이 간신히 도망쳐서 보카 데 라 세르피엔타 해안에 정박했지. 그들이 화물 일부를 구했지만 오래가진 못했어 – 현지 인디언 부족의 공격을 받았거든\n내 정보에 따르면, 그 해안에 있던 네덜란드인들은 전멸당했고, 화물은 인디언 마을로 옮겨졌어. 인디언들은 네덜란드의 화승총도 손에 넣었지만, 큰 피해를 입었지. 이게 바로 우리 기회야! 영국놈들이랑 네덜란드놈들이 아직도 그 지역에서 싸우느라 바빠서 잃어버린 플라이트엔 신경 쓸 겨를이 없어. 지금은 말이야... 자네에겐 배와 선원이 있잖아. 우리 거기로 가서 상륙해서 인디언들을 끝장내자고. 화물은 엄청나게 값지고 양도 많아\n나는 이미 정찰을 위해 소규모 원정을 보냈어 – 그게 내가 감당할 수 있는 전부였지, 돈 문제 알지? 믿을 만한 매수인도 있고, 내 검과 용병들도 믿어도 돼. 반반씩 나누는 거야, 그곳까지 가는 데 일주일밖에 없어. 자, 친구, 할 텐가?";
			link.l1 = "용서하시오, 나리, 하지만 나는 사양하겠소. 막 힘든 항해를 마쳤고, 수리나 선원 모집할 시간도 부족하오. 이런 신께 버림받은 곳에서도 사람은 모든 걸 가질 수 없는 법이지.";
			link.l1.go = "greguar_exit";
			link.l2 = "제법 위험한 일이지만, 수익도 괜찮고 모험도 기대된다니 당연히 나도 끼지!\n시간 낭비하지 말고 바로 시작하자!";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "안타깝군. 그럼 네가 결정해. 행운을 빌지, 나리. 어차피 나는 거기로 갈 거야. 남자라면 한번쯤 도전해 봐야지, 안 그래?";
			link.l1 = "행운을 빕니다, Valinnie 나리!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "좋은 선택이야, 친구! 돈 좀 더 필요하지? 그런데 네 동생은 잘 지내?";
			link.l1 = "나는 언제나 돈이 더 필요하지. 미셸? 내 동생은 건강하게 잘 지내고 있는데, 심심하다고 하더군. 가끔은 그 녀석이 부럽기도 해... 이제 출항할 시간이야!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "식은 죽 먹기지! 저놈들은 네덜란드 놈들과의 소동에서 살아남은 풋내기들이야. 더 내륙 깊숙이 들어가야 해, 내 탐험대가 분명 거기 있을 거야!\n";
			link.l1 = "너무 쉬운 것 같았지... 하지만 아직 축하하기엔 이르오, Valinnie 나리. 저쪽을 한번 보시오...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "젠장, 저 붉은 놈들! 우리를 거의 잡을 뻔했잖아! 이제 마을엔 여자랑 아이들만 남았다는 게 확실해. 움직여!\n";
			link.l1 = "너가 머스킷 얘기했던 것 같진 않은데, 난 못 봤어... 뭐, 됐다. 가자!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "무슨 말이야? 네덜란드 놈들이랑 우리가 다 죽였다는 거잖아!";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "도망치자고? 미쳤어? 우리 거의 다 왔잖아! 칠한 야만인 몇 놈이 무섭단 말이야?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "천하의 하찮은 놈들이군, 선장. 나는 유럽으로 돌아가겠소. 실망했소! 자네에게도, 이 겁쟁이들에게도, 그리고 이 피비린내 나는 땅에도!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "휴! 우리가 해냈어!";
			link.l1 = "하지만 대가가 너무 컸어! 봐, 우리 부대 거의 전원이 죽었잖아. 물러나야 해, Gregoire. 더 많은 전사들이 우리를 기다리고 있지 않다는 보장이 없어. 게다가, 전리품을 운반할 인원도 부족하잖아.";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "젠장! 슬프지만, 네 말이 맞아, "+pchar.name+": 야만인들이 다 죽었다 해도, 네덜란드 놈들이나 영국 놈들이 여기 상륙하기 전에 화물을 실어 나를 수는 없어. 지금 당장 떠나야 해! 이 빌어먹을 해안은 다 집어치워!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "휴! 해냈다! 잘했어, "+pchar.name+"! 이제 우리의 전리품을 위해 야만인들의 소굴로 가자! 이제 우리를 막을 수 있는 건 아무것도 없어!";
			link.l1 = "영국 놈들이랑 네덜란드 놈들이 아직 서로 싸우느라 바쁠 때 서둘러야지. 가자!";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "우린 잘했어, "+pchar.name+". 이제 우리가 할 일은 아무 의심도 사지 않고 화물을 파는 것뿐이야. 믿을 만한 구매자가 있는데, 자정에 라망탱 만에서 우리를 기다릴 거야. 장교들은 데려오지 말고, 만남 전에 그곳에 가지도 마. 의뢰인이 아주 예민한 녀석이거든.";
			link.l1 = "장사는 장사지. 화물은 반드시 팔아야 하고, 안전하게 처리해야 해. 그렇지 않으면 푸앵시에게 진 빚만 더 늘어나겠지. 좋아, 자정까지는 거기 갈게.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "끝났어. 화물은 내렸고, 의뢰인도 와 있어. 이제 말만 하면 돼.";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "놀랐지, 이 자식들아!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "아, 조니, 정말 대단한 녀석이군! 훌륭해! 할 말이라도 있나, "+pchar.name+"?";
			link.l1 = "아니. 사실, 맞아! 이게 뭐야?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "죽은 사람을 놀리지 마시오, 나리. 예의가 어디 갔소?.. 돈은 여기 있고, 화물은 나와 내 친구들이 처리하고 있소. 그들을 해안으로 보내지 않았소, 괜한 짓이었을 테니까. 특히 조니를 거기로 보냈다면 더더욱 그랬겠지. 저기 손에 큘버린을 든 붉은 피부 친구가 보이오? 알다시피, 조니는 자기 부족을 별로 좋아한 적이 없었소.";
			link.l1 = "알겠어... 이제 뭐 할 건데? 나도 죽일 거야?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "그래, 그래야겠지. 하지만 나는 감상적인 놈이라서 말이야. 그냥 가서 현금의 4분의 1만 가져가. 화물과 나머지 돈은 여기 내 곁에 남겨둘 거다. 영웅 흉내 내려고 하지 마라, 여긴 본토의 정글이 아니야. 네가 이길 가능성은 없어.";
			link.l1 = "그래서 너의 고귀함과 예의는 어디 갔지, Gregoire? 너한테 이런 모습을 볼 줄은 몰랐어. 난 떠나겠지만, 이 일은 잊지 않을 거야.";
			link.l1.go = "greguar_23";
			link.l2 = "나는 영웅 놀이 따위 안 해, 한 번도 그런 적 없어. 그냥 너희 모두를 죽일 거야! 먼저 이 아가씨들부터, 그다음엔 유탄발사기 든 원숭이, 그리고 마지막으로 너다!";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "이 해변에는 귀족도 깡패도 없소, 나리. 여기엔 다섯 명의 사내, 큰 대포, 그리고 희생자만 있을 뿐이오. 이런 일은 여기서 늘 일어나오만, 자네는 유일하게 옳은 선택을 했소. 잘했소. 자네 대신 이 자리에, 바로 지금, 두 명의 다른 사람이 설 수도 있었다는 걸 아는가? 그들도 거의 자네와 비슷한 자들이오. 하지만 자네가 여기 있고 그들은 없으니, 내 생각엔 그들은 그 때문에 죽게 될 것이오.";
			link.l1 = "무슨 말인지 잘 모르겠는데...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "언젠가 알게 될 거야. 그들은 마지막 교훈을 받지 못했지. 하지만 너는 받았어. 천만에. 잘 가라, 나리. 카리브에 온 걸 환영한다!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "아... 내가 가르친 학생들 중에 네가 제일 둔한 것 같구나. 뭐, 각자 자기 길이 있는 법이지!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "완벽한 타이밍이야! 우리는 간신히 카리브 놈들 무리에서 도망쳤어. 놈들이 네 쪽으로 가고 있었는데, 너 꼴을 보니 이미 만난 모양이군. 놈들 마을이 근처에 있는데, 우리의 문제는 이제 시작일 뿐이야.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = ""+GetFullName(pchar)+"! 여기 있었군! 그런데 왜 하나도 안 놀라지! 딱 맞춰 왔네, 친구. 우리는 간신히 카리브 놈들 무리한테서 도망쳤어, 그놈들이 네 쪽으로 가고 있었는데, 꼴을 보니 이미 한판 붙었구만.";
			link.l1 = "번창하길! 그리고 놀랍군! 또 인디언들한테 구멍을 내고 다니나? 셀리나는 잘 있겠지?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "이 원정에 합류한 건 어리석은 짓이었어. 내 딸이 날 다시 볼 수나 있을지 모르겠군. 셀리나? 음, 집에 앉아 당신을 그리워하며 꿈꾸고 있지! 마르티니크의 젊은이들은 이제 모든 희망을 잃었어... 있잖아, 이제는 이 머스켓을 산 걸 후회하지 않아. 튼튼한 화기야. 믿을 만하지. 게다가 또 다른 자살 임무에 참가할 이유가 하나 더 생겼지, 뭐. 물론 당신이 나타난 덕분에 이제는 조금 덜 자살 같지만. 저들의 마을이 근처에 있지만, 우리의 문제는 이제 막 시작일 뿐이야.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "전부 그런 건 아니야. 우리 정찰병이 총에 맞았지만 그래도 놈들 은신처까지 도달했지. 족장 본인이 직접 경호원들과 함께 이쪽으로 오고 있어. 그리고 네덜란드제 머스킷총도 가지고 있더군. 놈들은 수적으로도 우세하고, 완전히 분노에 차 있어. 족장은 부족에서 제일 강한 전사고, 그 부하들은 살아있는 악마들이야. 지금 여기서 빨리 결정해야 해. 싸울지, 아니면 도망칠지. 나는 솔직히 후자가 더 낫다고 생각해...\n";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "자네는 그놈들을 못 봤잖아, 이보게! 저 '야만인'들이 머스킷총을 들고 있는데, 그걸 아주 능숙하게 다룬다네. 누군가가 분명히 저들에게 사격을 가르친 게 틀림없어! 그러니 다시는 나보고 겁쟁이라고 부르지 마!";
			link.l1 = "진정하고 뭘 할지 결정하자. 아직 시간은 있어.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "듣고 있다네, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				Notification_Skill(true, 31, SKILL_SNEAK);
				link.l1 = "놈들한테 한판 붙자, 이 녀석들아! 저 언덕 뒤에 물건이랑 돈이 있다! 우리가 여기 온 건 그걸 위해서고, 절대 그냥 안 나간다. 머스킷 들고 있다 해도 인디언 무리 따위가 우리를 막을 순 없어! 저 자식들 묻어버리고 일 끝내자! 인원도 충분하니 매복할 기회가 있다. 네 명이 양쪽에서 불을 뿜으며 놈들을 맞이하고, 나머지는 여기서 자리 잡는다. 놈들 숫자 줄이고 끝장내자!";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (GetCharacterSkill(pchar, SKILL_SNEAK) < 31) Notification_Skill(false, 31, SKILL_SNEAK);
				if (n < 3) notification("Not enough people", "X");
				if (n > 0)
				{
					link.l1 = "놈들하고 한판 붙자, 얘들아! 저 언덕 너머에 물건이랑 돈이 있다! 우린 그걸 가지러 왔고, 절대 그냥 안 간다. 인디언 놈들이 머스킷을 들고 있어도 우리 못 막아! 저 자식들 묻어버리고 끝장내자!\n";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "우리에겐 모든 면에서 불리한 상황이야. 바로 뒤에 네덜란드 놈들이 있다는 것도 잊지 마라.";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "우린 살아서 집에 돌아왔어! 맹세컨대, 앞으로 몇 달은 모험은 충분하다니까, 하하! 이제 내 딸에게 가봐야겠어, 꼭 우리 집에 들러줘. "+pchar.name+". 그리고 제발, 조심해.";
			link.l1 = "약속은 못 하겠어, Prosper. 행운을 빌어!";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "내가 조심하라고 경고했잖아, 선장! 이 자식 수상하다고 생각했었지.";
			link.l1 = "번영하시오! 고맙소! 그런데 어떻게?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Poor lad, even though he was a pirate.";
			dialog.text = "조니가 말이 너무 많아졌어. 모래 위에 있던 그 인디언 녀석 말이야. 그가 사창가에 와서 여자를 꼬시려고 했지. 하지만 그들은 그를 받아주지 않았어. 조니가 화가 머리끝까지 나서 곧 부자가 될 거라며 소리치기 시작했지, 자기랑 친구들이 정글에서 어떤 선장을 죽이면 말이야. 나는 일이 어떻게 돌아갈지 보여서 네 장교에게 달려갔어, 그 장교도 이 마을에서 이미 꽤 유명해졌더라고. "+sTemp+" 너한테 진 빚이 많아, "+pchar.name+", 그러니 너무 고마워할 필요 없어.";
			link.l1 = "그래도 정말 고맙다, Prosper! 여기서 힘들었지... 너무 힘들었어. 내 선원으로 들어올래? 너 같은 장교가 필요해. 요즘은 충직한 놈들, 특히 명사수는 찾기 힘들거든.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "아니, 친구. 나는 내 딸에게 책임이 있어. 딸이 내게 모험을 그만두겠다고 맹세하라고 했거든. 그게 마지막 모험이었지. 젠장, 아쉽긴 하지만 세상 그 무엇보다 내 딸을 더 사랑하니까. 잘 가게,\n "+pchar.name+". 그리고... 셀리나가 항상 너 얘기만 해. 언젠가 우리한테 한번 들르지 않을래?";
			link.l1 = "누가 알겠어, 어쩌면 나도 그렇게 할지... 잘 있어라, 프로스페르! 네 딸이 좋은 신랑을 만나길 바란다... \n(혼잣말) 교훈 얻었지, 그레구아르 나리, 교훈 얻었어... 각자 자기 길이 있는 거라 했지... 이걸 잊지 않겠다.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "너 대체 누구야?";
			link.l1 = "화물은 우리가 가지고 있지. 관심 있나?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "하. 아주 흥미롭군. 내 의뢰인도 특히 그렇지. 수익이 얼마나 되지?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" 철목의, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" 배의 비단의, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" 밧줄과\n "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" 송진의.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "좋아. 철목 한 조각당 2200페소, 송진은 900페소, 선박용 비단은 1600페소, 밧줄은 1000페소다. 여기 뭘 가져왔나... 흠, 그래. "+iTotalTemp+" 페소다. 거래할래?";
			link.l1 = "거래 성사!";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "훌륭하군! 더 가져와라. 네덜란드 놈들은 인디언들에게 늘 인심이 후하지... 그런데 저 손님들은 누구지? 이게 뭐야?!\n";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "그래, 선장. 일부러 출항 전에 술을 너무 많이 마셨지.";
			link.l1 = "너? 어떻게?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "미안합니다, 선장님. 인디언들과 그 난장판 이후에 한두 잔 마셔야 했습니다. 어떤 아가씨가 있었는데, 백 페소를 주고 방을 잡았더니 그녀가... 그녀가...";
			link.l1 = "뭐라고? 너를 털었다고?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "안 돼! 걔가 사랑에 빠졌어! 젠장, 거기서 도망쳤어야 했는데! 그런데 네 친구가 나타나서는, 이 쓰레기, 네 옛 동료가 널 엿먹이고 죽이려고 한다고 나한테 소리 지르더라.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "잘했어, 프로스페르...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "프로스페르... 정말 미안하오. 당신의 딸은 내가 책임지겠소. 교훈을 얻었소, 그레구아르 나리... 뭐라고 했지? 각자 알아서 산다고? 이 말, 꼭 기억해야겠군.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "가시겠습니까, 선장님?";
			link.l1 = "그래. 수고했어. 술잔은 멀리하고, 우리가 저 미녀한테서 널 구해줄게. 가자.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
