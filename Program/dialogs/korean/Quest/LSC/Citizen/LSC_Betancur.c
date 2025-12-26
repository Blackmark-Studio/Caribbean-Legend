// Антонио Бетанкур - потомок Франциско Бетанкура
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "내 눈앞에서 사라져라! 무고한 사람들을 함부로 공격하는 도적들과는 상종하지 않겠다. 썩 꺼져라!";
				link.l1 = "흠...";
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "안녕! 무슨 일로 왔나, 친구?";
				link.l1 = TimeGreeting()+". 내 이름은 "+GetFullName(pchar)+". 제 소개를 하고 싶었습니다. 저는 이제 막 도착해서, 이 도시와 여기 사람들을 알아가는 중입니다.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 무엇을 도와줄까?";
				if(CheckAttribute(pchar, "questTemp.LSC.Betancur"))
				{
					link.l4 = "Antonio, 이 섬의 역사를 잘 안다고들 하던데. 너한테 물어볼 게 있어...";
					link.l4.go = "dolly";
				}
				dialog.text = "아, "+GetFullName(pchar)+"! "+TimeGreeting()+"! 뭐 필요해?";
				link.l1 = LinkRandPhrase("무슨 소식이야, 안토니오?", "섬에서 새로운 일이 있었나?", "최근 소문 좀 들려줄 수 있나?");
				link.l1.go = "rumours_LSC";
				link.l2 = "이 섬에 대해 몇 가지 물어보고 싶어.";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "어떻게 지내는지 궁금해서 와봤어. 잘 가, 나리!";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "훌륭하군. 우리 섬에 온 걸 환영해! 여기선 괜찮을 거야, 우리 모두가 하나의 크고 행복한 가족이니까. 뭐, 물론 나르발 놈들이랑 그 더러운 리바도스 녀석들은 빼고 말이지.\n내 이름은 안토니오야, 안토니오 데 베탕쿠르트. 혹시 들어본 적 있다면, 나는 프란시스코 데 베탕쿠르트의 손자다.";
			link.l1 = "프란시스코 데 베탕쿠르트? 그 이름 들어본 적 있어... 아, 맞다! 호세 디오스가 그에 대해 말해줬고, 이그나시오 알바라도의 기록에서도 읽었지!";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "나는 네가 말한 '호세 디오스'는 모르지만, 알바라도 선장은 오래전에 우리를 방문했었어 - 내가 어릴 때 직접 봤지. 그는 정의의 섬을 떠나 항해했고, 그 경험을 연대기에 남겼어. 그리고 내 할아버지 프란시스코는 스페인 제독이었고, 자신의 함대를 지휘했지.\n리바도스가 이곳 역사에 속한 이유는, 그들이 바로 그 함대의 기함인 타르타로스호의 흑인 노예 후손들이기 때문이야. 나르발들은 첫 백인 정착민들의 자손들이고, 그들은 타르타로스, 산 아우구스틴, 산 헤로니모의 선원들이었지.";
			link.l1 = "믿을 수 없군! 그럼 여기서 태어났어?";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "맞아요. 나는 이 섬을 개척한 남자의 손자요.";
			link.l1 = "알겠소. 만나서 반갑소, Antonio. 안녕히 가시오.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестовая часть
		case "dolly":
			dialog.text = "그래, 친구야, 뭐든 물어봐. 내가 아는 건 다 답해줄게.";
			link.l1 = "말해 봐, 산 헤로니모라는 갤리온을 기억하나?";
			link.l1.go = "dolly_1";
		break;
		
		case "dolly_1":
			dialog.text = "알지. 아주 특별한 배였지. 그 배에는 이상한 인도 우상이 있었는데, 더러운 이교도 리바도스 놈들이 그 우상에게 제물을 바쳤어.";
			link.l1 = "무슨 희생 제사 말이오? 마야처럼 사람 심장을 도려내고 목을 베는 짓이라도 했다는 거요?";
			link.l1.go = "dolly_2";
		break;
		
		case "dolly_2":
			dialog.text = "아니. 희생자가 우상 앞으로 끌려오면, 그 우상이 그들을 안으로 빨아들여서 영영 사라지게 했지. 악마의 짓이야! 신께 감사한 건, 그 우상이 배와 함께 가라앉아서 이제 더는 해를 끼치지 못한다는 거야.\n희생 제물은 항상 아침에 바쳐졌어. 해가 떠오를 때 우상이 금빛으로 변했거든. 그래서 야만인들은 그때 잡아온 희생자들, 주로 붙잡은 나르발들을 데려왔지.";
			link.l1 = "흥미롭군! 그 우상에 다가가 보려고 한 사람이 있던가?";
			link.l1.go = "dolly_3";
		break;
		
		case "dolly_3":
			dialog.text = "당연히 아니지! 첫째로, 리바도스 놈들은 자기들 말고는 누구도 산 헤로니모 근처에 못 오게 해. 둘째로, 정직한 가톨릭 신자는 악마의 장치와는 거리를 둬야 하거든.";
			link.l1 = "그렇군... 리바도스 녀석들을 별로 좋아하지 않는 모양이군.";
			link.l1.go = "dolly_4";
		break;
		
		case "dolly_4":
			dialog.text = "맙소사, 나는 그 더러운 이교도들이 정말 싫어! 내가 말했듯이, 내 할아버지(하느님 그 영혼을 거두소서)는 흑인들이 반란을 일으킨 배의 선장이었지, 그들의 두목 리바도스가 이끌었어. 그 검둥이 자식에게 천천히 죽음을 안겨준 것만이 그런 짓에 대한 유일한 올바르고 정의로운 응징이었지.\n나는 성 안나의 금고 열쇠를 가지고 있었어. 지금은 아무도 그 금고가 어디 있는지 몰라—아마도 바다 밑에서 게들이 뒤지고 있겠지—하지만 그 열쇠는 내게 소중한 기념품이었고, 도둑맞았어!\n분명히 흑인 놈들이 한 짓이야—금고를 찾으려고! 놈들이 성공할 리 없지; 너무 오래됐으니까, 하하! 쓰레기들...";
			link.l1 = "그래... 에헴, 아무튼, 흥미로운 이야기 고마워!";
			link.l1.go = "dolly_5";
		break;
		
		case "dolly_5":
			dialog.text = "환영하지! 언제든 들러!";
			link.l1 = "잘 가!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.Betancur");
			AddQuestRecord("LSC", "16");
		break;
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "듣고 있어, 친구.";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "그래서, 한 번도 정의의 섬을 떠난 적이 없다는 건가?";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "여기서 태어났는데... 그런데도 너는 나르발 클랜 소속이 아니라고? 나는 모든 토착 백인들은 나르발이라고 생각했는데.";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "그럼 이 정의의 섬에서 무슨 일을 하고 있나?";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "말해 봐, 너도 정의의 섬을 떠나서 세상을 보고 싶었던 적 있냐?";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "질문 없습니다. 실례합니다...";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "한 번도 없지. 하지만 내가 바보거나 편협하다고 생각하지 마. 나는 할아버지에게서 훌륭한 도서관을 물려받았고, 아버지에게서도 뛰어난 교육을 받았어. 역사, 지리, 천문학도 알고 있지. 영어, 프랑스어, 스페인어, 라틴어도 할 줄 알아. 썩어가는 난파선 말고는 본 적이 없지만, 내 마음속에서는 유럽, 중국, 인도까지 다녀왔지...\n실제로, 세상을 돌아다닌 대부분의 선원들보다 내가 훨씬 더 많이 안다고 말할 수 있을 거야.";
			link.l1 = "아마도...";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "다 그런 건 아니지만, 대부분 그렇지. 하지만 나는 나르발이 아니고, 그들 중 하나가 되고 싶지도 않아. 내가 왜 그래야 하지? 뜨거운 햇볕 아래서 몇 시간이고 보초를 서거나 리바도스와 싸우다 창자가 터져 죽으라고? 신이시여, 그런 건 사양이야! 나는 지식인이거든. 독립적으로 살면서 책 읽는 게 더 좋아.";
			link.l1 = "그렇군...";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "아버지가 나에게 꽤 괜찮은 유산을 남겨주셨고, 나는 그것을 현명하게 쓰고 있으니, 먹을 것을 구하려고 낡은 난파선에서 잡동사니를 뒤지거나, 있을지 없을지 모르는 보물을 쫓아다닐 필요는 없어.\n내가 확실히 아는 유일한 보물은 성 안나의 금고야. 커다란 쇠상자 안에 있다는데, 아직 아무도 찾아내지 못했지.\n언젠가 나는 이 섬의 구전 역사에 기반한 자세한 연대기를 쓸 거야 – 그거 어떻게 생각해?";
			link.l1 = "훌륭한 추구로군! 카리브 해에 그런 책을 위해 기꺼이 큰돈을 낼 사람을 적어도 한 명은 알고 있지...";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
		break;
		
		case "ansewer_4":
			dialog.text = "가끔 그래. 만약 조류와 폭풍을 뚫고 올 수 있는 배가 온다면, 아마 위험을 감수할지도 몰라. 내 책에 그렇게도 꼼꼼하게 묘사된 것들을 정말 보고 싶거든! 하지만 지금은, 그저 꿈일 뿐이지...";
			link.l1 = "가끔은 꿈이 이루어지기도 하지... 네가 직접 이룬다면 말이야.";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("아아, 도와줘! 도둑이다!!", "이 망할 놈, 내가 등 돌린 사이에 나를 털려고 하다니!", "그거 손대지 마! 그건 내 상자야! 누가 좀 도와줘!");
			link.l1 = "젠장!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "내 상자를 열다니, 뭐 하는 짓이야? 이대로 넘어갈 줄 알지 마!";
			link.l1 = "제기랄!";
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
			dialog.text = LinkRandPhrase("칼을 집어넣으시오, 나리! 불안하게 만드니까.", "여기서 칼 들고 돌아다니는 건 현명하지 않아, 친구. 집어넣어.", "아이고, 애처럼 칼 들고 뛰어다니지 말고 집어넣어.");
			link.l1 = LinkRandPhrase("좋아.", "원하시는 대로...", "죄송하오...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "이 도시 시민으로서 검을 거두라고 요구하오, 나리!", "검을 집어넣으시오, 나리! 소란을 피우고 있소.");
				link.l1 = LinkRandPhrase("좋아.", "원하시는 대로...", "말씀대로...");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "이봐, 제발, 칼 좀 집어넣어 줘. 그거 때문에 불안하잖아...", "나는 내 앞에서 무기를 휘두르는 남자들이 싫어. 무섭거든...");
				link.l1 = RandPhraseSimple("미안해.", "나는 이걸 치우고 있어.");
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
