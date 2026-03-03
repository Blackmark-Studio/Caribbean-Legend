// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕하세요, 나리. 처음 뵙는 얼굴이군요. 여기 처음 오셨습니까? 이 플랫폼에 처음 방문하신 겁니까?";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+"... 난 여기 처음이야, 그냥 둘러보면서 사람들을 알아가고 있어...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "들어봐, "+pchar.name+", 자꾸 방해하면 수리를 끝낼 수가 없어.";
					link.l1 = "그래, 그래, 그거 기억나. 폐를 끼쳐서 미안해!";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "아! 저것 좀 봐라! 익사한 자가 저승에서 돌아왔구나! 자, 말해봐라, 어떻게 그런 재주를 부린 거지? 네가 모를까 봐 말해두지만, 사람들은 네 장례식까지 치르고 네가 없는 채로 묻어버렸어...\n";
					link.l1 = "아쉽지만, 나는 아직 죽을 생각 없어. 비밀은 간단해 – 나는 쿠쿨칸의 우상을 밑부분만 건드렸거든. 그랬더니 도미니카로 순간이동됐지, 바로 카리브족 마을 한가운데로...";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"!";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "헨리크, 너한테 사업 제안을 하나 하지. 아주 중요한 일이야. 올레 크리스티안센이 네 얘기를 해줬거든. 그 사람은 '하얀 소년'이라고도 불려.";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "헨리크, 네가 부탁한 대로 '은화'를 충분히 가져왔어. 네 사람 한 명 몫에, 추가로 열 개 더. 자, 받아.";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "또 나야, Henrik. 네 옷은 어때? 수선할 수 있었어?";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= sti(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "네가 부탁한 그 금속, 충분히 있어. 가져가.";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "안녕, Henrik. 그래서, 잠수복 준비됐어?";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "끝났어, 내 문제는 다 해결했고 이제 잠수할 준비가 됐어. 언제 시작하지?";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "안녕, Henrik. 그래서, 잠수복은 준비됐어?";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "당신의 옷을 돌려주고 싶어.";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("재미있는 얘기라도 있어?","섬에 무슨 새로운 일이 있었나?","최근 소문 좀 들려줄래?");
				link.l1.go = "rumours_LSC";
				link.l3 = "그냥 어떻게 지내는지 궁금했어.";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "그리고 나는 헨리크 베데커야. 여기 사람들은 대부분 나를 '기술자'라고 부르지, 사실 그게 아주 정확한 표현이야.";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "당신이 Henrik Vedecker인가? 만나서 반갑소! 당신을 찾고 있었소.";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "너 만능쟁이겠지, 맞지?";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "아, 그래, 나르발들은 내 솜씨를 정말로 높이 사지. 내 도구 덕분에 바깥 고리의 난파선에서 많은 귀중품을 건져 올릴 수 있어서, 그걸로 도드슨 제독에게서 식량을 살 수 있거든.\n사실 과학과 탐험이 내 열정이야. 그래서 만약 너와 충분한 시간을 보내지 못하더라도 양해해 줘. 내 실험들이 거의 모든 시간을 차지하거든.";
			link.l1 = "알겠습니다. 괜한 일로 귀찮게 하진 않겠소, Vedecker 나리, 이 점은 분명히 약속하오. 당신을 만나게 되어 정말 기쁩니다!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "그랬어? 왜?";
			link.l1 = "올레 크리스티안센이 당신에 대해 말해줬어. 그는 '하얀 소년'으로도 알려져 있지.";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "아, 그 웃긴 녀석 말이지! 그래, 그래, 나도 알아. 그런데 그가 너한테 뭐라고 했어?";
			link.l1 = "내가 다음에 할 질문이 좀 멍청하게 들릴 수도 있다면 미안하지만... 그래도 물어볼게. 올레가 당신이 나한테 바닷속, 바닥까지 잠수하는 법을 가르쳐줄 수 있다고 하더군. 만약 그게 그냥 그의 상상이라면, 제발 나를 비웃지 말아줘.";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "맞아요. 나도 몇 번이나 직접 바닥까지 내려가 본 적이 있지. 하지만 이제는 더 이상 잠수하지 않아. 요즘 얕은 바다는 거대한 게들로 들끓고 있고, 보다시피 나는 그놈들과 싸울 힘이 없어. 나는 과학자일 뿐이야, 그런 것들과 싸울 수 없어.\n게다가, 예전에 잠수하던 다른 두 명, 두 명의 나르발도 있었는데, 결국 그들도 그만뒀지—바깥쪽 고리의 배 창고를 약탈하는 게 게로 가득 찬 곳에 잠수하는 것보다 훨씬 안전하다는 걸 알게 됐거든.\n이제는 내 장비도 거의 쓰지 않아, 잠수복이 망가진 이후로 지난 몇 달간 한 번도 잠수하지 않았어...";
			link.l1 = "정말로 바닥까지 잠수할 수 있는 잠수복이 있다고? 내가 잘못 들은 건가?";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "귀가 제대로 달렸구만, 젊은이. 이 잠수복은 내가 직접 고안하고 만든 거야. 두껍고 완전히 물에 적셔 방수 처리된 캔버스, 금속 부품, 그리고 나와 위르겐이 그의 대장간에서 단련한 강철 헬멧으로 만들었지\n게다가 나는 갑게, 무릎 보호대, 가슴 보호대, 부츠 등 금속으로 보강해서 게에게 물리는 것과 추가 무게에도 더 잘 견디게 했어\n특수 탱크에는 압축 공기가 들어 있어서 생명 유지와 일정 시간 동안 수중에서 머무를 수 있지. 이 잠수복은 유일무이한 것이고, 나는 꽤 자랑스럽게 생각해.";
			link.l1 = "훌륭하군. 하지만 그 옷이 망가졌다는 말은 했나?";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "안타깝게도 사실이야. 갑옷의 여러 부분이 금속 판으로 연결되어 있어서 유연성과 추가 보호를 제공했지만, 바닷물이 그 금속에 심하게 영향을 줬지. 오랜 사용 끝에 판이 녹슬고 방수 기능도 잃어버렸어.\n그래도 내가 손상을 알아채서 아무도 죽지 않게 막은 건 다행이야. 심지어 마른 잠수복 안에도 소금과 물이 조금 남아 있었는데, 이미 그 해로운 역할을 다 했더라고.";
			link.l1 = "음... 하지만 그 옷은 수리할 수 있잖아! 낡고 녹슨 부품을 새것으로 교체하면 되지... 맞지?";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "무슨 목적으로? 1년 뒤에 또 다시 교체하려고? 이 일이 얼마나 힘든지 알아? 관절이 유연한 옷을 조립하고 방수 처리까지 해야 하는데? 쉬지 않고 해도 최소 일주일은 걸려.";
			link.l1 = "그래서 네가 네가 만든 걸 그렇게 쉽게 버리려는 거냐?";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "아니, 당연히 아니지. 내게 생각이 있어. 물이나 소금에도 망가지지 않는 금속으로 이음새를 만들어야 해. 그리고 어떤 금속이 도움이 될지 알고 있지...";
			link.l1 = "그래서 뭐가 문제지?";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "문제는 이 금속이 매우 희귀하다는 거야. 나는 한 조각밖에 없는데, 그걸로는 확실히 부족하지. 최소한 열 조각, 아니면 열다섯 조각은 더 필요해.";
			link.l1 = "그리고 그게 뭐지... 네가 말하는 그 금속이란?";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "오, 이건 정말 독특한 금속이야. 많은 사람들이 그 가치를 제대로 알지 못하지. 내구성도 높고, 가공성도 뛰어나며, 무엇보다도 외부 환경에 전혀 영향을 받지 않아 – 물도, 소금도 이 금속을 해치지 못하지\n아마 이 금속을 이미 본 적이 있을 거야. 흰색이고 은처럼 보여서 스페인 사람들은 '은'이라고 불렀지. 하! 이건 은보다 백 배는 더 좋아! 금보다도 더 뛰어나지! 언젠가는 모두가 이걸 알게 될 거야, 하지만 아직 그때가 오지 않았을 뿐이야.";
			link.l1 = "이봐, 왜 다른 금속은 못 쓰는 거야? 그 접시들, 금으로 만들면 안 돼? 금이 녹슬거나 망가진다는 얘기는 들어본 적 없거든.";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "자네는 유연하고 생기 넘치는 머리를 가졌구나, 젊은이. 그 점은 반가운 일이야. 안타깝게도, 자네의 제안은 통하지 않을 것 같네. 금에 대한 생각이 제일 먼저 떠올랐지. 하지만 금은 너무 무르기 때문에 갑옷의 여러 부분을 연결하기엔 적합하지 않아\n유감스럽게도, 백금만이 유일한 재료라네. 몇 년이 걸려서라도 나는 오직 백금으로만 부품을 만들 생각이야. 하지만 이 섬에서 그 금속 조각을 본 적이 있어. 겉모습이 비슷해서 종종 은과 섞여 있지.";
			link.l1 = "흠. 내가 그 '은'을 충분히 찾아주는 대신, 그 잠수복을 빌려줘서 내가 물속에 들어갈 수 있게 해줄 건가?";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "물어볼 필요도 없어! 당연히 할 거야. 이미 게들 때문에 거기엔 잠수 안 하겠다고 말했잖아, 그리고 다른 누구도 하고 싶어하지 않아.";
			link.l1 = "그럼 그 쇳조각을 보여 줘. 내가 뭘 찾아야 하는지 알아야 하니까.";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "그래, 그걸 찾으러 가겠다는 거지? 훌륭해. 자, 이 조각을 예시로 가져가. 은광석이나 은괴들 사이에서 찾아봐. 쉽게 찾을 수는 없겠지만, 해낼 수 있을 거야. 은에는 작은 검은 점들이 있지만, 우리 금속은 맑고 은보다 훨씬 단단하지. 가장 쉬운 방법은 은화로 긁어보는 거야. 만약 동전이 상처를 입으면, 바로 그걸 찾은 거지.";
			link.l1 = "좋아. 바로 찾으러 갈 거야. 어디서 찾아봐야 할지 조언해줄 수 있어?";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a platinum ingot");
			dialog.text = "안타깝게도, 나는 몰라. 내가 어디서 찾을 수 있는지 알았다면 내가 직접 했겠지. 하지만 조언 하나는 해줄 수 있어. 리바도스 배들을 찾아봐. 나는 거기 안 가니까, 아마 거기 있을지도 몰라.";
			link.l1 = "생각해 보겠네, Henrik. 운이 따르길 바라지.";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "조각을 열 개 더 모아라. 그게 갑옷을 수리하는 데 필요한 최소한이야. 행운을 빈다!";
			link.l1 = "감사합니다. 안녕히 가시오, 정비공!";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "자, 자, 보여 줘... 훌륭하군! 잘했어, 젊은이! 어렵던가?";
			link.l1 = "꼭 그렇진 않아...";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "이제 수리를 시작할 수 있겠군. 시간 낭비하지 않고 내일부터 바로 시작할 거야. 정말 잠수하고 싶어서 안달이구나?";
			link.l1 = "정말이야. 나는 정말로 바닷속을 탐험해 보고 싶어.";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "그거 아주 잘됐군, 네가 잠수 준비를 할 때 부탁할 일이 하나 있을 거야. 하지만 그 이야기는 나중에 하자. 다섯 날 뒤에 나를 찾아와. 그때쯤이면 수리를 끝냈길 바란다.";
			link.l1 = "좋아. 행운을 빌어!";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "운도 분명 필요하지만, 갑옷 수리는 주로 솜씨가 중요하지. 게다가 네가 가져온 금속으로 판을 만들려면, 위르겐과 함께 하루 종일 용광로 옆에 있어야 해.";
			link.l1 = "그럼 더 이상 방해하지 않겠소. 다섯 날 뒤에 보지. 안녕히 계시오!";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (sti(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "그래. 위르겐이랑 내가 정말 고생했지, 네가 가져온 부품 양도 충분했어. 잠수복은 수리 완료됐고 준비도 다 됐어. 몇 가지 테스트만 더 하면 되는데, 문제없을 거라 확신해. 내일 오전 10시에 오면 돼 — 내가 탱크에 공기를 채워둘 테니, 네가 원하는 대로 할 수 있을 거야.";
				link.l1 = "훌륭해! 기대하고 있겠어. 내일 보자, Henrik!";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "실망시켜야겠군, "+pchar.name+". 내 예상대로 금속이 부족하군. 나는 필요해 "+FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty))+" 수리를 끝내려면 부품이 더 필요해. 다시 한 번 도움을 부탁해야겠어.";
				link.l1 = "음, 이런 전개는 예상 못 했는데. 좋아, 네가 부족한 금덩이를 찾아볼게.";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "기다리고 있겠소. 이 정도면 충분할 거라 확신하시오. 그냥 그것들을 가져오기만 하면 내가 하루 만에 일을 끝내겠소.";
			link.l1 = "그러길 바라... 또 보자!";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", sti(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "훌륭해! 이제 잠수복이 복원될 거야. 몇 가지 테스트만 더 하면 되는데, 분명 괜찮을 거라고 확신해. 내일 오전 10시에 와. 내가 탱크에 공기를 채워둘 테니, 네가 원하는 대로 할 수 있을 거야.";
			link.l1 = "훌륭해! 기대하고 있을게. 내일 보자, Henrik!";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "the day after tomorrow";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "tomorrow";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "But I have to find Nathaniel Hawk first before I dive."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "그래, 잠수복은 준비됐고 공기도 채워져 있어. 들어가도 돼.";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "좋아. 하지만 지금은 잠수할 수 없어, 내... 친구인 네이선 호크와 관련된 문제를 해결해야 해. 그를 찾을 수가 없어. 잠수복은 잠깐 기다릴 수 있을까?";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "훌륭하군! 언제 시작하지? 지금이야?";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "그래. 기다릴 수 있지. 친구를 1년 내내 찾을 생각이야?";
			link.l1 = "그래, 안 할게. 어쩌면 오늘이라도 그를 찾을 수 있을지도 몰라. 그와 볼일을 마치면 바로 너를 찾아올게.";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "네, 부탁하네. 잠수할 준비가 되면 오게.";
			link.l1 = "고마워!";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "지금 당장이라도 괜찮아. 하지만 먼저 간단히 설명해 줄게. '피닉스' 플랫폼에서 잠수를 시작하게 될 거야; 산 가브리엘의 선미에서 갈 수 있어. 거기에는 밑바닥까지 내려갔다가 다시 올라올 수 있는 승강기가 있어. 그게 돌아오는 유일한 방법이야\n그러니 물속에서 승강기 위치를 꼭 기억하고 길을 잃지 않도록 해. 잠수복의 산소통은 20분 정도 잠수할 수 있을 만큼만 들어 있어. 시간을 잘 확인하지 않으면 질식하게 될 거야\n승강기에서 너무 멀리 떨어지면 제때 돌아올 수 없으니 조심하고, 만약 우리 얕은 바다를 벗어나면 – 넙치처럼 납작하게 눌려버릴 거야, 신께서 지켜주시길 바라야지\n조심하고 게를 주의해. 너무 가까이 가면 공격할 거야. 꼭 필요하지 않으면 위험을 감수하지 마; 게 무리를 전부 상대할 수는 없고, 그 아래에서는 빠르게 도망칠 수도 없어.";
			link.l1 = "게들은 내가 처리할게. 나머지는 내가 맡았어. 너무 깊이 들어가지 말고, 도르래에서 멀리 떨어지지 마, 그리고 시간도 잊지 마라. 언제 들어가도 돼?";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "언제든지 원하면 되지만, 오전 7시부터 오후 9시까지만 가능해. 어두우면 아무것도 볼 수 없을 거야.";
			link.l1 = "알겠어.";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "그게 바로 그거야. 플랫폼 옆 방에서 잠수복을 가져가. 잠수 끝나면 벗어서 나한테 가져와. 내가 다시 공기를 채워줄게. 하지만 하루에 한 번 이상 잠수하려고 하지 마. 20분만 잠수하고 압축 공기를 마셔도 건강에 안 좋아.";
			link.l1 = "글쎄, 그럼 하루에 한 번 이상은 잠수하지 않겠어.";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "이해해 줘서 기쁘네. 이제 가게, 행운을 빌지!";
			link.l1 = "고마워!";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "그래서, 아직 여기 있는 이유가 뭐지? 옷이 널 기다리고 있어.";
				link.l1 = "그래, 그래. 가는 중이야.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "그래서, 첫 잠수는 어땠어?";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "아주 훌륭하군, 그리고 결과에도 만족해. 난 침몰한 갤리온에서 석상 우상을 발견했어. 리바도스가 예전에 그 우상에게 제물을 바쳤다는 얘기를 들었지. 헤인리크, 혹시 그 우상에 대해 더 잘 아는 사람을 알고 있나?";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "좋아. 내가 했어! 정말 흥미로웠지만, 약간 아슬아슬하기도 했지.";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "우리 역사에 관심 있어? 그럼 안토니오 베탕쿠르트에게 가 봐. 그는 여기서 태어났어. 플루트 플루토에서 살고 있지. 그 사람이 모르면, 아무도 모를 거야.";
			link.l1 = "훌륭하군! 꼭 찾아가 보겠어.";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "여기에 잠수복을 두고 가. 내일이나 아무 날이나 다시 오면, 내가 공기를 채워줄게.";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "물론이지. 여기 네 옷이야. 고마워!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "물론이지. 바로 가져올게!";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "그래, 내 장비 가져왔나?";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "알겠어. 여기 네 옷이야. 고마워!";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "당장 하겠습니다!";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "네, 물론이지. 잠수복은 이미 시험해 보고 공기도 채워 놨어. 서약서는 가지고 있나? 50만 페소?";
				if (sti(pchar.money) >= 500000)
				{
					link.l1 = "그래, 물론이지. 자, 받아.";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "이런! 깜빡했네. 바로 가져올게...";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "네, 물론이지. 잠수복은 이미 시험했고 공기도 채워져 있어. 평소처럼 '피닉스' 플랫폼을 확인해.";
				link.l1 = "그럼 내가 잠수할게. 고마워!";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "좋아. 내일이나 나중에 다시 오게. 내가 옷을 준비할 테니.";
			link.l1 = "고마워요, 정비공!";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "옷을 돌려주면 돈을 돌려받게 될 거야. 공정한 거래지.";
			link.l1 = "고마워, 정비공! 이제 잠수하러 갈게.";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "잠깐만요! 무슨 조각상 말씀인가요? 아-아, 이제 알겠어요. 침몰한 배 '산-헤로니모'에 있는 그 우상 말이죠? 그럼 리바도스의 이야기들이 진짜였던 건가요?";
			link.l1 = "정확해! 그리고 전설 같은 건 없어. 내가 아는 한, 군도에는 더 두 개의 우상이 있는데, 그걸 만진 사람을 서로 다른 우상으로 순간이동시키지, 순환 구조로 말이야.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "알겠어, 알겠어. 네 말을 믿어야겠군, 비과학적인 헛소리지만 말이야. 순간이동이니, 조각상이니... 하! 누가 그런 걸 생각이나 하겠어, 그런 게 어떻게 작동한다는 거지?";
			link.l1 = "그냥 나를 믿고 여기서 논리를 찾으려고 하지 마. 거짓말하는 거 아니야.";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "좋아. 그런데 네가 순간이동할 때 그 옷을 잃어버리진 않았겠지?";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "그래, 안 했지. 말하자면, 그게 나를 카리브족한테서 구해줬거든. 여기 있어.";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "그래, 내가 가진 건 아니었지. 말하자면, 그게 나를 카리브족한테서 구해줬어. 하지만 지금은 가지고 있지 않아.";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "그러니까 그걸 나한테 가져와, 젠장! 그걸 다시 가져오기 전엔 얘기 안 할 거야, 알겠어?";
			link.l1 = "진정해, 정비공. 내가 돌려줄게!";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "아, 정말로 내 옷을 가져왔구나! 고맙다, 슬슬 걱정되기 시작했었거든.";
				link.l1 = "걱정할 필요 없었어. 돌려주겠다고 약속했잖아.";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "내 옷 가져오기 전에는 여기 오지도 마.";
				link.l1 = "좋아, 좋아.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "아주 좋군. 새로 하나 만들까 생각하기 시작했었는데, 그건 적어도 1년은 걸릴 일이었지... 네가 훌륭한 판단을 보여주고 내 물건을 온전하게 돌려줘서 기쁘다. 선물도 하나 주겠다.";
			link.l1 = "진심이야?";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "그래, 맞아! 네가 내 옷을 고쳐줬고, 처음 기회가 왔을 때 버리지도 않았지. 그동안 잘 챙겨줬고, 결국 이렇게 다시 돌려줬구나. 아무튼, 여기 좋은 공구 상자가 있어. 사용법을 익혀 둬. 이걸로 유용한 것들을 많이 만들 수 있을 거야.";
			link.l1 = "그리고 내가 기술자한테 뭘 더 바라겠어! 역시 공구함이지! 고마워, Henrik. 감동이야... 이런 선물 받을 자격도 없는데.";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("You have received a toolbox");
			PlaySound("interface\important_item.wav");
			dialog.text = "네가 무엇을 받을 자격이 있고 없는지 나는 더 잘 안다. 가져가라! 너한테 쓸모 있을 거다. 하지만 우상으로 순간이동하는 네 버릇 때문에, 50만 페소를 맹세해야만 다시 옷을 주겠다.";
			link.l1 = "이런 젠장! 뭐, 알겠어... 혹시 몰라서 그러는 거지...";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "그래. 그런데 언젠가 그걸 들고 도망치면 어쩌지? 그때는 그 돈이 내 보상금이 되겠군.";
			link.l1 = "좋아, 헨릭. 동의하지. 솔직히 말해서, 네가 다시는 그걸 내게 주지 않을 줄 알았거든.";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "가망 없어. 오십만 내놓으면 다 네 거야.";
			link.l1 = "좋아! 그럼 평소처럼 내가 잠수하러 가져가도 돼? 내일부터?";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "정확해.";
			link.l1 = "고마워! 또 보자, Henrik!";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("거기서 뭐 하는 거야, 응? 도둑놈!","저것 좀 봐! 내가 잠깐 생각에 잠긴 사이, 네가 내 상자를 뒤지기로 했구나!","내 내함을 뒤지러 온 거냐? 그냥 넘어가지 않을 거다!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "뭐?! 내 상자들을 뒤져볼 생각이었어? 그냥 넘어가지 않을 거야!";
			link.l1 = "어리석은 계집애!...";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("이봐, 무기는 집어넣는 게 좋겠어. 그거 들고 있으니 불안하거든.","있지, 여기서는 칼 들고 돌아다니는 거 용납 안 돼. 집어넣어.","이봐, 중세 기사처럼 칼 휘두르며 돌아다니는 짓은 하지 마. 집어넣어, 너한테 어울리지 않아...");
			link.l1 = LinkRandPhrase("좋아.","그래.","말씀대로...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 도시의 시민이니 칼을 집어넣어 줬으면 하네.","이봐, 나는 이 도시의 시민이야. 그러니 칼을 집어넣어 줬으면 해.");
				link.l1 = LinkRandPhrase("좋아.","그래.","말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"조심해, 친구. 무기 들고 돌아다니면 내가 긴장할지도 몰라...","사람들이 무기를 뽑은 채 내 앞을 지나가는 건 싫어. 무섭거든...");
				link.l1 = RandPhraseSimple("알겠어.","내가 가져간다.");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
