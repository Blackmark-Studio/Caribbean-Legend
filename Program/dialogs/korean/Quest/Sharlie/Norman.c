// Абрахам Норман
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
		case "First time":
			dialog.text = "무엇이 필요하십니까?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "norman_us":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("무슨 일이야? 네 길이나 가고, 네 일이나 신경 써. 그냥 나 좀 내버려 둬.","이봐, 이봐, 친구. 산책 나가는 거야? 좋아, 그냥 계속 걸어가서 아브라함 나리한테 신경 끄라고. 그분도 산책 중이시거든. 바닷바람 좀 쐬려고 말이야.","안녕, 친구. 수다 떨고 싶어? 그런데 한 가지 문제가 있지. 지금은 말할 기분이 아니거든. 그러니 딴 사람 귀찮게 해. 선술집 가서 쉬어. 럼주나 한잔해...");
				link.l1 = "이봐, 아브라함, 혹시 최근에 이슬라 테소로에서 미겔 디초소라는 남자를 만난 적 있나? 이 근방에선 제법 유명한 인물이거든.";
				link.l1.go = "tieyasal";
				break;
			}
			dialog.text = NPCStringReactionRepeat(LinkRandPhrase("무슨 일이냐? 네 갈 길 가고, 네 일이나 신경 써라. 그냥 나 좀 내버려 둬.","이봐, 이봐, 친구. 산책 나가는 거야? 그래, 그냥 계속 걸어가서 아브라함 나리 좀 내버려 둬. 저분도 산책 중이시거든. 바닷바람 좀 쐬러 나오신 거야.","이봐, 친구. 수다 떨고 싶어? 문제는 딱 하나야: 난 지금 대화할 기분이 아니거든. 그러니까 딴 놈이나 귀찮게 해. 선술집 가서 쉬든가. 럼주나 한잔 해..."),LinkRandPhrase("이봐, 선원. 뭐야, 머리가 단단한 거야? 난 분명히 말했잖아.","이봐, 가서 좀 쉬어. 귀가 좀 먹은 것 같군.","이봐, 친구, 뭐야, 너 바보냐? 이미 다 설명해줬잖아."),"이봐, 나 화나게 하지 마라. 내가 지금까지 뭍돼지들을 얼마나 많이 죽였는지 알아? 한 놈 더 죽인다고 별로 달라질 것도 없어.","좋아, 이제 나를 열받게 했군. 녹슨 칼을 뽑든가 아니면 죽을 힘 다해 도망치든가 해라. 두 번째를 추천하지...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("알겠어, 친구. 더 이상 귀찮게 안 할게.","알겠어, 알겠다고...","이봐, 너 바다의 천둥처럼 보이는데! 알았어, 난 여기서 빠질게.","뭐라고?!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "norman_us";
		break;
		
		case "norman_fes":
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = LinkRandPhrase("뭐 필요해, 이봐? 네 갈 길 가고, 네 일이나 신경 써. 그냥 나 좀 내버려 둬.","이봐, 이봐, 친구. 산책 나가는 거야? 그래, 그냥 계속 걸어가서 아브라함 나리한테 신경 끄라고. 저분도 산책 중이시거든. 바닷바람 좀 쐬려고 말이야.","이봐, 친구. 얘기 좀 할래? 그런데 한 가지 문제가 있어. 난 지금 대화할 기분이 아니거든. 그러니까 딴 사람 귀찮게 해. 선술집 가서 쉬든가. 럼주나 한잔 해...");
				link.l1 = "이봐, Abraham, 혹시 최근에 Isla Tesoro에서 Miguel Dichoso라는 남자를 만난 적 있나? 이 근방에선 꽤 유명한 인물이거든.";
				link.l1.go = "tieyasal";
				break;
			}
			switch (hrand(5))
			{
				case 0:
					dialog.text = "멈춰라! 내가 이 섬의 총독이다. 뭐야, 안 믿는 거냐?!";
					link.l1 = "당연히 알지! 이슬라 테소로의 총독을 모르는 사람이 어디 있겠어...";
					link.l1.go = "norman_fes0_fight";
					link.l2 = "하, 그럴 거면 차라리 제독이라고 불러 보시지, 내가 꼭 믿고 사주겠네!";
					link.l2.go = "norman_fes0_peace";
				break;
				
				case 1:
					dialog.text = "주목하라! 보아라 - 바르바리고 제독님이시다! 내 유명한 기병도검을 못 알아보겠나?";
					link.l1 = "죄송합니다, 제독님! 이제부터는 더 주의하겠습니다.";
					link.l1.go = "norman_fes1_peace";
					link.l2 = "자네의 기병도는 널리 알려져 있지. 안타깝게도 지금은 멍청이 손에 있군.";
					link.l2.go = "norman_fes1_fight";
				break;
				
				case 2:
					dialog.text = "보다시피, 나는 지금 망명 중이오. 나는 몽크 장군의 추가 지시를 기다리고 있소. 내 숨겨진 왕족 신분을 누설하지 말아 주시오. 크롬웰의 첩보망은 귀가 길기로 유명하오.";
					link.l1 = "물론이지요, 폐하. 아무도 카를 2세가 서인도에 숨어 있다는 사실을 알지 못할 것입니다.";
					link.l1.go = "norman_fes2_fight";
					link.l2 = "그렇다면 나는 교황 인노첸시오 10세겠군.";
					link.l2.go = "norman_fes2_peace";
				break;
				
				case 3:
					dialog.text = "무슨 일이 있었던 거냐, 블레이즈? 이틀 동안이나 너를 찾고 있었다. 너는 완전히 아버지 니콜라스를 잊어버린 거냐!";
					link.l1 = "아버지, 지금 당신과 이야기할 시간 없어! 너무 바빠.";
					link.l1.go = "norman_fes3_peace";
					link.l2 = "착각하셨소, 나리. 내 이름은 "+GetFullName(pchar)+".";
					link.l2.go = "norman_fes3_fight";
				break;
				
				case 4:
					dialog.text = "쉬-잇... 나는 데이비 존스다. 말해 봐, 죽음이 두렵냐?";
					link.l1 = "물론이지, Jones 나리. 특히 숙취가 심한 다음엔 더 그렇지.";
					link.l1.go = "norman_fes4_fight";
					link.l2 = "한 명의 죽음은 비극이지만, 천 명의 죽음은 그저 통계일 뿐이다.";
					link.l2.go = "norman_fes4_peace";
				break;
				
				case 5:
					dialog.text = "나는 새 희곡을 빨리 완성해야 해. 네가 반드시 내가 '존재할 것인가, 존재하지 않을 것인가'라는 구절을 완성하도록 도와줘야 해?!";
					link.l1 = "그것이 문제로다! 우리가 모욕을 참아내고 그냥 넘어가야 할까...";
					link.l1.go = "norman_fes5_fight";
					link.l2 = "술 한잔, 그건 좋지. 하지만 난 사창가에서 병이라도 옮을까봐 전혀 놀랍지 않겠어!";
					link.l2.go = "norman_fes5_peace";
				break;
			}
		break;
		
		case "norman_fes0_fight":
			dialog.text = "무슨 헛소리를 하는 거야? '테소로'라니?! 차라리 버뮤다라고 부르지 그러냐! 이 섬은 내 이름을 따서 노먼 섬이라고 불러. 잊지 마라! 내가 지리 좀 가르쳐줘야겠군...";
			link.l1 = "흥! 무슨 소리야?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes0_peace":
			dialog.text = "네 말이 맞아, 선원. 사실 나는 정말 바르바리고 제독이야, 하지만 이건 우리끼리만 아는 거다. 행군할 준비해. 곧 출발한다. 그게 너한테 쓸모가 있을 거야.";
			link.l1 = "정말 감사하오!";
			link.l1.go = "norman_fes0_exit";
		break;
		
		case "norman_fes0_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 12)
			{
				GiveItem2Character(pchar, "pistol2");
				Log_Info("You've received a three-barreled shotgun");
			}
			else
			{
				if (GetDataDay() == 23 && GetDataMonth() == 2)
				{
					GiveItem2Character(pchar, "mushket1");
					Log_Info("You've received a match-lock musket");
				}
				else
				{
					GiveItem2Character(pchar, "cartridge");
					Log_Info("You've received a paper cartridge");
				}
			}
		break;
		
		case "norman_fes1_fight":
			dialog.text = "지금 누가 바보인지 곧 알게 될 거다. 검을 들어라!";
			link.l1 = "진심이야?!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes1_peace":
			dialog.text = "내가 뭐랬어! 자, 내 건강을 위해 한잔해.";
			link.l1 = "원샷하시오, 제독 나리!";
			link.l1.go = "norman_fes1_exit";
		break;
		
		case "norman_fes1_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 13)
			{
				GiveItem2Character(pchar, "gold_dublon");
				Log_Info("You've received a gold doubloon");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 4)
				{
					GiveItem2Character(pchar, "chest");
					Log_Info("You've received a chest of doubloons");
				}
				else
				{
					AddMoneyToCharacter(pchar, 5);
				}
			}
		break;
		
		case "norman_fes2_fight":
			dialog.text = "내 이름을 퍼뜨리지 말라고 했잖아! 이제 널 위험한 목격자로 처리해야겠군...";
			link.l1 = "오, 이 순간만을 기다렸어!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes2_peace":
			dialog.text = "용서해 주십시오, 각하! 이런 차림새로는 알아보지 못했습니다. 부디, 진정한 가톨릭 신자로서 이 소박한 선물을 받아 주시기 바랍니다.";
			link.l1 = "광기가 속삭이기 시작한다...";
			link.l1.go = "norman_fes2_exit";
		break;
		
		case "norman_fes2_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 14)
			{
				GiveItem2Character(pchar, "amulet_10");
				Log_Info("You've received the Wonderworker Amulet");
			}
			else
			{
				if (GetDataDay() == 25 && GetDataMonth() == 12)
				{
					GiveItem2Character(pchar, "totem_04");
					Log_Info("You've received the Talisman of the Accomplice");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral3");
					Log_Info("You've received a wax candle");
				}
			}
		break;
		
		case "norman_fes3_fight":
			dialog.text = "다들 나만 노려! 내 아들이랑 똑같이 생긴 첩자를 잡았어! 틀림없이 토마스가 내 남은 눈까지 빼앗으려고 보낸 거야!";
			link.l1 = "꺼져, 이 멍청아!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes3_peace":
			dialog.text = "피곤해 보이고 얼굴도 안 좋구나, 꼬마야. 얼른 가서 치료나 받아라.";
			link.l1 = "고마워!";
			link.l1.go = "norman_fes3_exit";
		break;
		
		case "norman_fes3_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 15)
			{
				GiveItem2Character(pchar, "potion4");
				Log_Info("You've received a potion");
			}
			else
			{
				if (GetDataDay() == 19 && GetDataMonth() == 6)
				{
					GiveItem2Character(pchar, "talisman8");
					Log_Info("You've received the Scorpion Amulet");
				}
				else
				{
					GiveItem2Character(pchar, "potion1");
					Log_Info("You've received remedial essence")
				}
			}
		break;
		
		case "norman_fes4_fight":
			dialog.text = "겁내지 마, 친구. 봐, 죽는 건 전혀 무섭지 않다니까...";
			link.l1 = "장난이 아니었군!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes4_peace":
			dialog.text = "분명 겁먹지 않았군. 그럴 줄 알았지. 그게 바로 용기야!";
			link.l1 = "넌 참 웃기는 늙은이구나...";
			link.l1.go = "norman_fes4_exit";
		break;
		
		case "norman_fes4_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 17)
			{
				GiveItem2Character(pchar, "cirass6");
				Log_Info("You've received a fire-eater waistcoat");
			}
			else
			{
				if (GetDataDay() == 1 && GetDataMonth() == 1)
				{
					GiveItem2Character(pchar, "cirass3");
					Log_Info("You've received a parade cuirass");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral18");
					Log_Info("You've received some tobacco");
				}
			}
		break;
		
		case "norman_fes5_fight":
			dialog.text = "넌 형편없는 시인이구나, 선원. 혹시 네 칼이 네 혀보다 더 날렵한 건 아니겠지?";
			link.l1 = "카람바! 네가 가진 기병도는 장난이 아니구나!";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "norman_fes5_peace":
			dialog.text = "젠장! 너한텐 일이 꽤 순조롭게 풀렸잖아! 네 상상력에 이 정도면 어때!";
			link.l1 = "또 오시오.";
			link.l1.go = "norman_fes5_exit";
		break;
		
		case "norman_fes5_exit":
			DialogExit();
			NextDiag.CurrentNode = "norman_fes_again";
			PlaySound("interface\important_item.wav");
			PlaySound("interface\important_item.wav");
			if (GetDataDay() == 16)
			{
				GiveItem2Character(pchar, "potionrum");
				Log_Info("You've received a bottle of rum");
			}
			else
			{
				if (GetDataDay() == 28 && GetDataMonth() == 11)
				{
					GiveItem2Character(pchar, "totem_01");
					Log_Info("You've received a throat of cast iron");
				}
				else
				{
					GiveItem2Character(pchar, "Mineral17");
					Log_Info("You've received a glass flask");
				}
			}
		break;
		
		case "norman_fight_again":
			dialog.text = "아하, 너를 알아보겠구나! 하하!";
			link.l1 = "또...";
			link.l1.go = "fight";
		break;
		
		case "norman_fes_again":
			dialog.text = "좋아, 친구, 할 얘긴 다 했으니 이제 가봐.";
			link.l1 = "말씀대로 하겠습니다...";
			link.l1.go = "exit";
			NextDiag.TempNode = "norman_fes_again";
		break;
		
		case "tieyasal":
			dialog.text = "디초소? 걔가 왜 필요하지, 응?";
			link.l1 = "글쎄, 난 그 사람이 필요해. 그냥 꼭 필요하다고. 그래서, 그 사람 봤어?";
			link.l1.go = "tieyasal_1";
			link.l2 = "무슨 소리야, 내가 그를 왜 필요로 하냐고? 미겔은 내 오랜 동료야, 친구라고도 할 수 있지. 그는 원래...\n";
			link.l2.go = "tieyasal_2";
			link.l3 = "그가 예전에 샤크 도드슨을 위해 그랬던 것처럼 내게도 새 배를 끌어오길 바라네.";
			link.l3.go = "tieyasal_3";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l4 = "Miguel Dichoso가 사람을 죽였어. 그래서 내가 그를 찾고 있는 거야.";
				link.l4.go = "tieyasal_4";
			}
			npchar.quest.Tieyasal = "true";
		break;
		
		case "tieyasal_1":
			dialog.text = "너한텐 그 사람만 있으면 돼... 그 사람만 있으면 된다니까! 네게 필요한 건 미겔 디초소뿐이야! 아니, 나는 그를 본 적 없어. 아주 오래됐지. 내가 도와줄 수 있는 건 없어, 선원.";
			link.l1 = "흠... 좋아, 잘 가.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_2":
			dialog.text = "친구라니... 그 자는 친구를 산더미처럼 쌓아뒀더군. 곧 친구가 하나 줄게 생겼지...";
			link.l1 = "이봐, 영감. 왜 그러는 거야?";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_3":
			dialog.text = "그래, 디초소는 어디서 보든 그런 일의 달인이야. 하지만 그가 어디 있는지는 몰라. 한 번 들렀다가 다시 떠났거든. 그러니 알렉수스에게 가 보게, 선원. 그가 자네에게 멋진 배를 만들어 줄 거야.";
			link.l1 = "흠... 정보 고마워, 친구.";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_4":
			dialog.text = "그래서 디초소가 누구를 해치워서 네가 그 자식 뒤를 쫓게 된 거냐, 이 친구야?";
			link.l1 = "블레이즈 샤프";
			link.l1.go = "tieyasal_5_1";
			link.l2 = "니콜라스 샤프";
			link.l2.go = "tieyasal_5";
			link.l3 = "알론소 데 말도나도";
			link.l3.go = "tieyasal_5";
			link.l4 = "교황";
			link.l4.go = "tieyasal_5_bud_joke";
		break;

		case "tieyasal_5_1":
			dialog.text = "쉿... (주위를 둘러본다) 너도 디초소가 블레이즈 샤프를 죽였다고 생각하나?";
			link.l1 = "그래. 그리고 그냥 촉만 있는 게 아니야 — 증거도 있어. 선박 일지에 기록이 남아 있거든...";
			link.l1.go = "tieyasal_6"
		break;

		case "tieyasal_5_bud_joke":
			dialog.text = "이제 농담까지 하자는 거야? 아무런 존경심도 없군! 자, 더 가까이 와봐...";
			link.l1 = "말도 안 돼.";
			link.l1.go = "fight";
			NextDiag.TempNode = "norman_fight_again";
		break;
		
		case "tieyasal_5":
			dialog.text = "아... 뭐, 그 자를 죽였고 그게 전부야. 여기 돌아다니는 살인자가 얼마나 많은지 알아? 둘 중 하나는 다 그래! 아니, 선원. 디초소는 오래전에 본 게 마지막이야. 내가 도와줄 수 있는 건 없어.";
			link.l1 = "안타깝군...";
			link.l1.go = "exit";
		break;
		
		case "tieyasal_6":
			dialog.text = "조용히 해, 이봐. 이름이 뭐였더라? 기억이 잘 안 나네...";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "tieyasal_7";
		break;
		
		case "tieyasal_7":
			dialog.text = "들어봐, "+pchar.name+"디초소가 불쌍한 블레이즈를 죽였어. 내가 내 두 눈으로 똑똑히 봤지, 그래-그래. 그런데 아무도 내 말을 안 믿어. 알겠지, 다들 내가 미쳤다고 생각하거든. 자기네 동료지만 미쳤다고. 나도 한때는 니콜라스 샤프 선장 일행 중 최고의 백병전 장교였다고! 그땐 참 좋았지! 하지만 결국 발톱도, 발굽도, 렌즈도 잃고 땅에 묶이고 말았어.\n뭐라고? 아, 맞다! 모두가 샤크가 범인이라고 생각했지만, 사실 아니었어. 절대 아니야. 샤크의 이빨, 도드슨의 부적이 있었지만, 그걸 거기 둔 건 디초소였어.\n아마 둘이 프리깃 ‘포춘’호에서 같이 항해할 때 샤크한테서 훔쳤을 거야. 그날따라 잠이 안 와서 밖에 산책 나갔거든. 디초소가 샤프의 저택에 몰래 들어가는 걸 봤고, 누가 비명을 지르고 신음하는 소리도 들었지. 곧이어 디초소가 저택에서 나왔는데, 손에 피가 잔뜩 묻어 있었어.\n아무도 내 말을 안 믿었지, 절대. 그날 섬에 디초소는 없었고 샤크만 있었으니까. 그리고 샤크의 이빨이 발견됐지. 하지만 난 디초소를 봤어, 확실해. 아무도 그날 그가 거기 있었다는 걸 몰랐지. ‘행운아’는 정말 교활하고 무서운 놈이야...";
			link.l1 = "너만이 디초소를 '행운아'라고 부른 게 아니야. 왜 그렇게 부르지? 별명이라도 되는 거야?";
			link.l1.go = "tieyasal_8";
		break;
		
		case "tieyasal_8":
			dialog.text = "스페인어 모르는 거야, 이봐? 'Dichoso'는 교황쟁이들 말로 '행운아'란 뜻이야. 행운의 미겔, 운 좋은 미겔. 그게 저 녀석 이름이지.";
			link.l1 = "운 좋은 미겔?... 흠. 뭔가 생각나게 하는군. 흠. 그 말, 어디서 많이 들어본 것 같은데...";
			link.l1.go = "tieyasal_9";
		break;
		
		case "tieyasal_9":
			dialog.text = "음, 성이 디초소라고 해도, 나는 여전히 그가 스페인 사람이라고 생각하지 않아. 아니, 아니야. 그는 스페인 사람이 아니야. 겉모습은 스페인 사람처럼 보이긴 하지만.";
			link.l1 = "그럼 그는 뭐란 말이오? 영국인인가, 프랑스인인가?";
			link.l1.go = "tieyasal_10";
		break;
		
		case "tieyasal_10":
			dialog.text = "그 얘기가 아니야, 선원... 아, 용서하시오, 선장님. 그래, 디초소는 프랑스어를 아주 멋지게 지껄이지, 당신 못지않게 말이오. 영어도 마찬가지고. 하지만 그의 핏줄에는 인디언 피가 흐르고 있소. 내 평생 그런 사람들을 많이 봤지. 쉽게 알아차리긴 어렵지만, 그는 혼혈이오. 내가 보장하오.";
			link.l1 = "그가 현지어를 할 줄 아나?";
			link.l1.go = "tieyasal_11";
		break;
		
		case "tieyasal_11":
			dialog.text = "아, 젠장 알 게 뭐야. 어쩌면 알지도 몰라. 아니, 잠깐만. 알아! 그 사람은 늘 이상한 언어로 이상한 문장을 중얼거리곤 했지. 그러면서 무슨 현자라도 된 양 무서운 표정을 짓고 볼까지 부풀렸어. 예를 들면, 이런 식이었지: cogito ergo sum! 그리고는 눈을 굴리며 선원들 반응을 살폈어. 아니면 이렇게 외치기도 했지: aut Caesar, aut nihil! 그 밖에도 별별 말을 다 내뱉었어. 다 기억나진 않아.";
			link.l1 = "저건 인디언 언어가 아니야. 라틴어야. 라틴어... 라틴어라고?! 젠장!";
			link.l1.go = "tieyasal_12";
		break;
		
		case "tieyasal_12":
			dialog.text = "왜 이렇게 깜짝 놀라냐, 이봐? 왜 소리 지르는 거야? 뱀한테라도 물렸어? 어디로 갔는데?";
			link.l1 = "처음부터 왜 눈치채지 못했지! 모든 게 내 눈앞에 있었는데! 라틴어! 미겔... 행운의 미겔!!!";
			link.l1.go = "tieyasal_13";
		break;
		
		case "tieyasal_13":
			dialog.text = "이봐, 친구. 그만 좀 소리치지 않을래? 사람들이 다 쳐다보잖아. 뭐가 그렇게 속상한 거야, 선원... 아니, 선장?";
			link.l1 = "나는 미겔 디초소가 누구인지 진짜로 알아. 그는 스페인 사람이 아니야. 프랑스인이었어! 아, 내가 너무 눈이 멀었구나!";
			link.l1.go = "tieyasal_14";
		break;
		
		case "tieyasal_14":
			dialog.text = "아니야, 멍청아. 걔는 프랑스 놈이 아니야. 혼혈이거든. 백인 아버지가 카리브 해의 아라와크나 미스키토 같은 인디언 소녀, 아니면 이차 여자랑 놀아났고, 그래서 거룩한 미겔 디초소가 태어난 거지. 너는 못 보겠지만, 나는 보여. 그 눈에 다 써 있거든...\n";
			link.l1 = "그의 출신에 관한 문제는 잠시 제쳐두자고. 아브라함, 그는 어디 있지?! 여기 있었던 거야?!";
			link.l1.go = "tieyasal_15";
		break;
		
		case "tieyasal_15":
			dialog.text = "쉬... 그래, 그가 여기 있었어. 하지만 떠났지. 이제 이슬라 테소로에는 없어.";
			link.l1 = "그가 여기에 왜 온 거지? 무슨 배를 가지고 있나?";
			link.l1.go = "tieyasal_16";
		break;
		
		case "tieyasal_16":
			dialog.text = "그의 배는 갤리언이야. 큰 전쟁 갤리언이지. 대체 뭘 하러 여기 온 거지... 아무튼, 이리저리 기웃거리면서 질문을 하더라고. 그런데 내가 그 녀석 대화를 엿들었지, 그래, 맞아! 어떤 샤를 드 모르라는 사람을 찾고 있었어. 그래, 그거야. 샤를 드 모르. 잠깐, 그게 바로 너잖아, 샤를 드 모르! 그 녀석이 찾던 사람이 너였어, 친구.";
			link.l1 = "무슨 이유인지 아시오?";
			link.l1.go = "tieyasal_17";
		break;
		
		case "tieyasal_17":
			dialog.text = "글쎄, 너랑 선술집에 가서 럼주나 마시려고 온 건 절대 아니었지. 그는 널 잡으려고 했어. 그래, 맞아! 널 잡으려고! 큰일 났어, 선장!";
			link.l1 = "의심하지 않아...";
			link.l1.go = "tieyasal_18";
		break;
		
		case "tieyasal_18":
			dialog.text = "그쪽은? 왜 그를 찾고 있지? 아, 알겠다, 알겠어: 죽이려고! 죽여, 죽여버려, 그 자식! 블레이즈 샤프의 복수를 해! 블레이즈는 정말 멋진 녀석이었지. 기억나, 어릴 때부터 니콜라스랑 똑같았어.";
			link.l1 = "디초소는 어디로 갔지?";
			link.l1.go = "tieyasal_19";
		break;
		
		case "tieyasal_19":
			dialog.text = "그는 블루웰드로 가는 길이었어. 샤를 드 모르를 숲의 악마의 보호 아래에서 찾아야 한다고 했지. 하지만 자기 사람들은 여기에 두고 갔어... 잠깐. 벌써 네가 들킨 것 같군!\n";
			link.l1 = "누가 나를 눈치챘지?";
			link.l1.go = "tieyasal_20";
		break;
		
		case "tieyasal_20":
			dialog.text = "디초소의 부하들이오. 그가 여기서 당신을 감시하라고 명령했소. 아, 나도 알아, 알아! 조심하시오, 선장. 이슬라 테소로의 암초 주위엔 배들이 둘러싸고 있고, 그놈들이 당신 목을 노리며 기다리고 있소. 그 선장은 여우처럼 교활하니, 속지 말도록 하시오.";
			link.l1 = "해보겠소...";
			link.l1.go = "tieyasal_21";
		break;
		
		case "tieyasal_21":
			dialog.text = "그리고 한 가지 더 있네. 자, 내 기병도를 가져가게. 받아, 받아. 자네에게 필요할 거야. 이건 바로 바르바리고 선장 본인의 검이네. 아주 훌륭한 칼이지. 군도에서 최고라네. 머뭇거리지 말고 가져가게. 블레이즈 샤프의 원수는 반드시 갚을 테니!";
			link.l1 = "감사합니다, Abraham.";
			link.l1.go = "tieyasal_22";
		break;
		
		case "tieyasal_22":
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveItems(npchar, "blade_29", 1);
			sTemp = GetBestGeneratedItem("blade_29");
			GiveItem2Character(pchar, sTemp);
			sld = ItemsFromID(sTemp);
			sld.Balance = 2.0;
			GiveItem2Character(npchar, "blade_19"); 
			EquipCharacterbyItem(npchar, "blade_19");
			Log_Info("You've received Barbarigo's sword");
			PlaySound("interface\important_item.wav");
			dialog.text = "이제 가거라. 가, 누군가가 너를 지켜보고 있다. 똑똑한 척하든, 멍청한 척하든 상관없다. 아무렴 어때. 조심만 해라!";
			link.l1 = "고마워, 친구. 네가 얼마나 큰 도움을 줬는지 모를 거야. 행운을 빌어!";
			link.l1.go = "tieyasal_23";
		break;
		
		case "tieyasal_23":
			DialogExit();
			pchar.questTemp.Tieyasal.MigelKnow = "true";
			AddQuestRecord("Tieyasal", "4");
			pchar.quest.Tieyasal_ITAttack.win_condition.l1 = "location";
			pchar.quest.Tieyasal_ITAttack.win_condition.l1.location = "Bermudes";
			pchar.quest.Tieyasal_ITAttack.function = "Tieyasal_CreateITShips";
			pchar.questTemp.Tieyasal = "islatesoro";
		break;
		
		case "fight":
			iTemp = 20-sti(GetCharacterItem(npchar, "potion2"));
			TakeNItems(npchar, "potion2", iTemp);
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
