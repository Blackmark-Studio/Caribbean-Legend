//Jason общий диалог цыганок
// ugeen <-- добавил продажу мышьяка из под полы
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;
	int poison_price;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "아, 안녕, 자기야. 무슨 일이야?";
			link.l1 = "아무것도 아니겠지.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("당신에게 물어볼 것이 있어.","정보가 필요해.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				dialog.text = LinkRandPhrase("자기야, 금화를 좀 나눠줄 수 있겠어? 네 미래를 알려줄게.","이봐, 선원, 그렇게 급하게 가지 마! 미래가 궁금하지 않아?","담배 좀 주고 은화 몇 닢만 줘, 용감한 청년. 그러면 네 미래를 점쳐 주지. (윙크) 비밀스러운 집시 마법을 듣고 싶나?");
				link.l1 = "미안하지만, 이제 가봐야겠어.";
				link.l1.go = "exit";
				// --> мангароса
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "이봐, 땜장이 아줌마, 네네 사람들이 약초랑 독에 능하다는 거 알아. 이 식물에 관심 있을지도 모른다고 들었어. 한번 봐봐. 어떻게 생각해?";
					link.l5.go = "mangarosa";
				}
				if (CheckCharacterItem(pchar, "cannabis7") && CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "gipsy_trade" && !CheckAttribute(npchar, "quest.mangarosa"))
				{
					link.l5 = "이봐, 까만 눈동자야, 너한테 줄 게 있어... 이건 망가로사야. 좀 살래?";
					link.l5.go = "mangarosa_trade1";
				}
				// <-- мангароса
				link.l2 = "내 운세를 봐줄 수 있나?";
				link.l2.go = "guess";
				link.l3 = RandPhraseSimple("당신에게 질문이 있습니다.","정보가 필요해.");
				link.l3.go = "quests";//(перессылка в файл города)
				npchar.quest.meeting = "1";
			}
			// --> Тёмные воды исцеления
			if (CheckAttribute(pchar, "questTemp.DWH_Start") && !CheckAttribute(pchar, "questTemp.DWH_gipsy") && npchar.city == "SentJons")
			{
				link.l6 = "나는 병자를 돌보는 집시 여인을 찾고 있소. 혹시 그대요?";
				link.l6.go = "dwh_ne_ta";
			}
			// <-- Тёмные воды исцеления

			if (!CheckAttribute(npchar, "quest.poison_price") && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && rand(2) == 0)
			{
				link.l4 = "이봐, 까만 눈동자, 쥐 잡는 독 있냐? 내 배에서 아주 골칫덩이들이라서.";
				link.l4.go = "get_poison_1";
			}
			NextDiag.TempNode = "First time";
		break;

//-------------------------------------------------гадание-------------------------------------------------
		case "guess":
			dialog.text = "물론이지, 잘생긴이. 동전 좀 주고 오른손을 보여줘. 네 미래를 알려주고 재앙을 피하게 도와줄게. 나는 절대 속이지 않아! 돈 돌려주는 보장도 있지!";
			link.l1 = "이쯤에서 네 동료가 내 주머니를 털 것 같은 기분이 드는군... 마음이 바뀌었어. 지금은 그럴 기분 아니야.";
			link.l1.go = "exit";
			link.l2 = "얼마나 많은 돈을 원하지?";
			link.l2.go = "guess_1";
		break;
		
		case "guess_1":
			dialog.text = "아이고, 자네 지갑이 허락하는 만큼, 그리고 자네 마음이 원하는 만큼이지. 에잇 피스를 더 많이 줄수록 내가 더 멀리 미래를 내다볼 수 있다네!";
			link.l1 = "100페소";
			link.l1.go = "guess_rate_1";
			link.l2 = "500페소";
			link.l2.go = "guess_rate_2";
			link.l3 = "1000 페소";
			link.l3.go = "guess_rate_3";
			link.l4 = "5000페소";
			link.l4.go = "guess_rate_4";
		break;
		
		sTemp = GuessText();
		case "guess_rate_1"://никаких плюшек
			if (sti(pchar.money) >= 100)
			{
				AddMoneyToCharacter(pchar, -100);
				dialog.text = "아, 자네의 자비에 감사하네, 잘생긴 젊은 매야! 이제 잘 들어보게:  "+sTemp+"";
				link.l1 = LinkRandPhrase("헤! 그거 참 흥미롭군. 한번 생각해 보지...","정말인가? 그 점은 생각해 보지...","오, 정말이야? 진심이야? 그거 기억해 두지...");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "가장 흉측하고 피할 수 없는 불운이 너를 기다리고 있다네. 조롱하는 자를 저주하라! 검은 구름이 네 머리 위에 몰려들고, 벌이 반드시 내릴지어다!";
				link.l1 = "하하! 내가 정말 돈을 줄 거라고 생각했나, 이 집시 마녀야? 비켜! 종교재판소가 너를 잡아가길 바란다!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_2"://немного в везение или скрытность
			if (sti(pchar.money) >= 500)
			{
				AddMoneyToCharacter(pchar, -500);
				dialog.text = "아, 고맙구나, 잘생긴 내 어린 매야! 이제 들어보아라:"+sTemp+"";
				link.l1 = LinkRandPhrase("헤! 그거 참 흥미롭군. 기억해 두지...","정말인가? 생각해 보지...","오, 정말이야? 진심이야? 좋아, 그건 기억해 두지...","이봐, 벌써 좀 나아진 것 같아!");
				link.l1.go = "exit";
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 30+rand(10));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 30+rand(10));//скрытность
			}
			else
			{
				dialog.text = "가장 흉측하고 피할 수 없는 불행이 너를 기다리고 있다. 조롱하는 자를 저주하노라! 검은 구름이 네 위에 몰려들고, 벌이 반드시 너를 찾아내길!";
				link.l1 = "하하! 내가 정말 돈을 줄 거라고 생각했나, 이 집시 마녀야? 비켜! 종교재판소가 너를 잡아가길 바란다!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_3"://здоровье + везение или скрытность, харизма
			if (sti(pchar.money) >= 1000)
			{
				AddMoneyToCharacter(pchar, -1000);
				dialog.text = "아, 은화를 주어서 고맙구나, 잘생긴 젊은 매야! 이제 들어보거라:"+sTemp+"";
				link.l1 = LinkRandPhrase("헤헤! 아주 흥미로운걸. 그 점은 생각해 보지...","정말인가? 그것에 대해 생각해 보지...","오, 정말이야? 진심이야? 그래, 그건 기억해 두지...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 1);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				if (hrand(1) == 0) AddCharacterExpToSkill(pchar, "Fortune", 50+rand(20));//везение
				else AddCharacterExpToSkill(pchar, "Sneak", 50+rand(20));//скрытность
			}
			else
			{
				dialog.text = "가장 흉측하고 피할 수 없는 불운이 너를 기다리고 있다. 조롱하는 자를 저주하노라! 먹구름이 네 머리 위에 몰려들고, 벌이 반드시 너를 찾게 될 것이다!";
				link.l1 = "하하! 내가 너한테 돈을 줄 거라고 진짜 생각했나, 이 집시 마녀야? 비켜! 이단심문소가 너를 잡아가길 바란다!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_rate_4"://умения в оружие, везение+скрытность, здоровье, харизма
			if (sti(pchar.money) >= 5000)
			{
				AddMoneyToCharacter(pchar, -5000);
				dialog.text = "오라라! 이렇게 후하게 베풀어 주다니, 잘생긴 젊은 매야, 고맙구나! 이제 잘 들어봐:\n"+sTemp+"";
				link.l1 = LinkRandPhrase("헤! 그거 참 흥미롭군. 생각해 보지...","정말인가? 그 점은 생각해 보지...","오, 정말이야? 진심이야? 좋아, 그거 기억해두지...");
				link.l1.go = "exit";
				AddCharacterHealth(pchar, 2);
				AddCharacterExpToSkill(pchar, "Leadership", 40);
				AddCharacterExpToSkill(pchar, "Fortune", 50+rand(100));//везение
				AddCharacterExpToSkill(pchar, "Sneak", 50+rand(50));//скрытность
				AddComplexSelfExpToScill(20, 20, 20, 20);
			}
			else
			{
				dialog.text = "가장 흉측하고 피할 수 없는 불행이 너를 기다리고 있다. 조롱하는 자를 저주하라! 먹구름이 네 위에 몰려들고, 벌이 반드시 너를 찾아낼 것이다!";
				link.l1 = "하하! 내가 너한테 돈을 줄 거라고 진짜로 생각했냐, 이 집시 마녀야? 비켜! 인퀴지션이 너를 잡아가길 바란다!";
				link.l1.go = "guess_exit";
			}
		break;
		
		case "guess_exit":
			DialogExit();
			AddCharacterHealth(pchar, -10);
			LAi_CharacterDisableDialog(npchar);
		break;
//<-- гадание

// --> продажа мышьяка
		case "get_poison_1" :
			npchar.quest.poison_price = (hrand(3) + 1) * 10;
			if(hrand(10) == 3 || IsCharacterPerkOn(pchar, "Trustworthy"))
			{				
				dialog.text = LinkRandPhrase("오, 잘 모르겠네, 잘생긴이! 얼마 전에는 쥐를 잡아달라고 도와달라는 녀석이 있었고, 그다음엔 누가 요새의 병사들에게 독을 탔지. 그 일 때문에 우리 섬 사람들은 꽤나 곤란했어. 경비병들이 살인범을 찾을 때까지 2주 동안 우리를 심문했거든. 그 자는 적국의 첩자였어.","그대의 의도를 내가 어떻게 믿을 수 있지? 혹시 명예로운 결투를 벌일 용기는 없으니, 귀족을 독살하려는 것 아닌가?","누군가 선술집에서 상인을 독살하고 그의 모든 소지품을 훔쳤다고 들었어. 그 남자는 죽기 전에 오랫동안 고통을 겪었지. 입에서 거품이 나오고 얼굴이 가지처럼 퍼렇게 변했다더군.. 그 일, 당신이 한 거야, 내 사랑?");
				link.l1 = "너희 집시 계집애들은 정말 할 말이 많구나! 걱정 마라, 아가씨, 난 아무도 독살할 생각 없어. 그건 여자들이 쓰는 수법이지, 내 방식이 아니야. 남자한텐 내 칼이 있지. 하지만 저 저주받은 쥐들은 도저히 못 다루겠어.";
				link.l1.go = "get_poison_2";
				if (IsCharacterPerkOn(pchar, "Trustworthy")) Notification_Perk(true, "Trustworthy");
			}
			else
			{
				dialog.text = "나를 함정에 빠뜨리려는 거군! 아니오, 나리, 나는 독 따위는 없어. 식물과 약초는 있지만, 독약은 없어.";
				link.l1 = "그래, 뭐든지. 나한테 악귀 붙이지 마라.";
				link.l1.go = "exit";
				Notification_Perk(false, "Trustworthy");
			}	
		break;
		
		case "get_poison_2" :
			dialog.text = "오, 이렇게 잘생기고 용감한 남자라니! (속삭이며) 돈 내. "+sti(npchar.quest.poison_price)+" 두블룬.";
			if (PCharDublonsTotal() >= sti(npchar.quest.poison_price))
			{				
				link.l1 = "비싸군... 이 물건, 제대로 효과가 있어야 할 텐데.";
				link.l1.go = "get_poison_4";
			}
			else
			{
				link.l1 = "말도 안 돼! 집에서 똑같은 걸 오 피스톨에 샀다고! 그 돈이면 쥐는 내가 직접 다 잡겠다!";
				link.l1.go = "get_poison_3";
			}
		break;
		
		case "get_poison_3" :
			dialog.text = "그럼 네가 직접 잡아. 나 귀찮게 하지 말라고. 다음엔 경비를 부를 거야.";
			link.l1 = "경비는 필요 없어, 마녀야, 나는 나간다.";
			link.l1.go = "exit";
		break;
		
		case "get_poison_4" :
			PlaySound("interface\important_item.wav");
			RemoveDublonsFromPCharTotal(sti(npchar.quest.poison_price));
			TakeNItems(pchar, "rat_poison", 1);
			DialogExit();
		break;
// <-- продажа мышьяка

	// --> Мангароса
		case "mangarosa":
			dialog.text = LinkRandPhrase("식물을 보여줘, 얘야... 흠... 내가 너한테서 사도 되겠구나. 300피스의 에잇, 어때?","그쪽으로 안내해 줘, 잘생긴이... 흐흐... 좋아, 그걸 위해 이백오십을 낼 수 있어.","어디 보자... 오! 흥미로운 예시군! 이백 페소! 거래할까?")"";
			link.l1 = LinkRandPhrase("오, 주님이시여... 까만 눈동자야, 나는 시골 촌뜨기가 아니야. 이 식물 알아. 망가로사야...","오, 정말이야?! 이건 완벽한 망가로사 표본이군. 나를 속이려고 하지 마라, 집시.","아하, 그리고 네가 이렇게 보잘것없는 돈에 이 망가로사를 내줄 거라고 생각하는 거냐.");
			link.l1.go = "mangarosa_1";
		break;
		
		case "mangarosa_1":
			dialog.text = "좋아, 좋아, 잘생긴 녀석. 이 식물에 대해 뭔가 아는 것 같군. 50두블론이다. 내놔.";
			link.l1 = "잠깐만! 이게 어떻게 쓰이고, 무슨 용도인지 알고 싶어. 그것에 대해 말해 줄 수 있나? 너희 사람들은 이 작은 풀 한 포기에 금을 엄청나게 지불하려 하더군!";
			link.l1.go = "mangarosa_2";
		break;
		
		case "mangarosa_2":
			// тут работает харизма
			if (sti(pchar.questTemp.Mangarosa.g_count) == 5 || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 10+hrand(25)+hrand(30, "1"))
			{
				dialog.text = "흠... 뭐, 조금 이야기해 줘도 나쁠 건 없겠지. 이 식물은 특별한 기술 없이는 아무것도 할 수 없을 테니까.";
				link.l1 = "듣고 있네.";
				link.l1.go = "mangarosa_3";
			}
			else
			{
				dialog.text = LinkRandPhrase("내 백성들은 금을 많이 낼지도 모르지만, 결코 그들의 비밀을 밝히지는 않을 것이오.","금은 금이고, 비밀은 비밀이지, 젊은이... ","그래, 돈은 낼 생각이지만 말해줄 생각은 없지.")+"그래서 내게 망가로사를 팔 생각이오? 우리 시세는 오십 두블룬이니, 그보다 더 줄 사람은 없을 것이오.";
				link.l1 = "오, 좋아... 어차피 나한테 상관없어. 50두블론이야. 가져가.";
				link.l1.go = "mangarosa_trade";
				link.l2 = "내 말을 이해하시오, 나는 그걸 팔고 싶지 않소. 왜 그게 필요한지 알고 싶을 뿐이오. 내게 아는 것을 나누면, 공짜로 주겠소.";
				link.l2.go = "mangarosa_exit";
			}
		break;
		
		case "mangarosa_trade":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "동전 가져가라, 어린 매야. 그리고 한 가지 더, 이런 식물을 더 가져오너라. 하지만 우리는 한 번에 하나씩만 살 수 있다네, 많은 돈을 가지고 다니지 않으니. 경비병들이 우리 같은 사람을 믿지 않고 괴롭히는 걸 즐기거든...\n";
			link.l1 = "좋아. 더 찾으면 가져올게.";
			link.l1.go = "mangarosa_trade_exit";
		break;
		
		case "mangarosa_trade_exit":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "gipsy_trade";
			AddQuestRecord("Mangarosa", "3");
		break;
		
		case "mangarosa_exit":
			dialog.text = LinkRandPhrase("말도 안 돼! 팔기 싫으면 그냥 팔지 마. 난 아무것도 안 알려줄 거야.","우리 집시 비밀을 너 같은 외부인에게 절대 안 알려주지! (퉤) 팔기 싫으면 말고, 지옥이나 꺼져라.","이봐, 그건 네가 알 일이 아니야. 오십 두블룬에도 팔기 싫어? 그럼 가서 상점 아가씨한테 이백 페소에 팔아봐.");
			link.l1 = LinkRandPhrase("그럼 너한테는 안됐군! 네 선원 중 다른 누군가가 어차피 나한테 말해줄 거야. 그리고 그 여자가 이 식물을 선물로 받게 될 거다. 또 보자!","왜 이렇게 고집을 부리나? 네가 말하지 않으면, 다른 사람이 말할 거다. 그리고 그 여자가 이 망가로사를 선물로 받게 되겠지. 잘 있어라.","너 입에서 마늘 냄새가 진동하는군. 결국 내가 원하는 건 얻게 될 거다. 네 동료 중 다른 놈은 더 말이 많고 식물도 공짜로 가져다주겠지. 또 보자.");
			link.l1.go = "exit";
			npchar.quest.mangarosa = "true";
			pchar.questTemp.Mangarosa.g_count = sti(pchar.questTemp.Mangarosa.g_count)+1;
		break;
		
		case "mangarosa_trade1":
			dialog.text = "왜 묻는 거지, 매야?! 당연하지! 내놔.";
			link.l1 = "금화 50닢을 내놓아라.";
			link.l1.go = "mangarosa_trade1_1";
			link.l2 = "이런! 내가 그걸 잃어버렸거나 내 배에 두고 온 것 같군. 아쉽게 됐네. 그럼...";
			link.l2.go = "exit";
			npchar.quest.mangarosa = "true";
		break;
		
		case "mangarosa_trade1_1":
			RemoveItems(pchar, "cannabis7", 1);
			TakeNItems(pchar, "gold_dublon", 50);
			PlaySound("interface\important_item.wav");
			dialog.text = "걱정 마라, 사기치지 않을 거다. 동전 가져가.";
			link.l1 = "망가로사를 가져가라. 더 찾으면 가져다주지.";
			link.l1.go = "exit";
		break;
		
		case "mangarosa_3":
			dialog.text = "우리는 꽃봉오리를 특별한 방식으로 빻은 다음, 말리고, 씨앗과 줄기를 골라내고, 담배와 섞어 파이프에 꼭꼭 눌러 담아 그 혼합물을 피워. 그러면... 잊을 수 없는 효과를 얻지. 술에 취한 것 같은 기분이 들지만, 다음 날 두통은 없어. 식물 한 송이면 파이프 두어 스무 번은 충분히 피울 수 있지.";
			link.l1 = "이제 알겠어! 이 비밀 기술을 나한테 가르쳐줄 수 있겠어? 보수는 충분히 줄게...";
			link.l1.go = "mangarosa_4";
		break;
		
		case "mangarosa_4":
			dialog.text = "젊은 매야, 내 말을 믿어라, 이건 네게 필요 없는 거다. 끼어들지 마라, 그 식물이 널 망칠 거야. 정신을 흐리게 하고 몸도 불어나게 하지. 나한테 묻지도 마라. \n하지만... 내 앞에 서 있는 건 용감한 사내구나, 칼을 든 바다의 사내... 어쩌면 선장일지도 모르겠군?";
			link.l1 = "맞는 말이오.";
			link.l1.go = "mangarosa_5";
		break;
		
		case "mangarosa_5":
			dialog.text = "자, 잘 들어라. 망가로사는 훨씬 더 고귀한 목적에 쓸 수 있고, 너에게도 쓸모가 있을 거다. 우리 치유사 중 한 명이 그 모든 비밀을 알고 있지. 네가 필요한 사람은 바로 그 여자야.\n식물을 나에게 주면 그녀의 이름과 어디서 찾을 수 있는지 알려주겠다. 하지만 그녀가 비밀을 너에게 털어놓게 하는 건 네 몫이다.";
			link.l1 = "좋아. 식물을 가져가고, 네네 집시 마법사를 어떻게 찾는지 말해 줘.";
			link.l1.go = "mangarosa_6";
		break;
		
		case "mangarosa_6":
			RemoveItems(pchar, "cannabis7", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "그녀의 이름은 아멜리아야. 현명한 이들이 말하길, 그녀는 스페인 본토 남서쪽 해안 어딘가, 바다에서 멀지 않은 모래언덕 사이의 작은 집에서 혼자 산다고 해.";
			link.l1 = "아, 제발, 좀 더 구체적으로 말해 줄 수 없겠소?";
			link.l1.go = "mangarosa_7";
		break;
		
		case "mangarosa_7":
			dialog.text = "너는 뱃사람이자 용감한 매지만, 나는 아니야. 내가 말해준 곳에서 그녀를 찾아봐. 그녀의 집은 해안가에서 아주 가까워. 스페인 본토 남서쪽에 있는 만 근처에 있어 – 뱃사람이라면 알 테지.";
			link.l1 = "좋아, 내가 한번 찾아볼게...";
			link.l1.go = "mangarosa_8";
		break;
		
		case "mangarosa_8":
			dialog.text = "마랑가로사를 그녀에게 가져가. 그렇지 않으면 말도 안 할 거야. 그리고 두블룬도 꼭 챙겨가. 공짜로 가르쳐줄 거라 생각도 하지 마!";
			link.l1 = "참으로 탐욕스럽군. 그 점은 고려해 보지. 이야기해 줘서 고맙다!";
			link.l1.go = "mangarosa_9";
		break;
		
		case "mangarosa_9":
			DialogExit();
			npchar.quest.mangarosa = "true";
			DeleteAttribute(pchar, "questTemp.Mangarosa.g_count");
			pchar.questTemp.Mangarosa = "amelia";
			pchar.questTemp.Mangarosa.Tell = "true"; // калеуче
			AddQuestRecord("Mangarosa", "4");
			// создаем и ставим Амелию
			sld = GetCharacter(NPC_GenerateCharacter("Amelia", "gipsy_3", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			SetFantomParamFromRank(sld, 10, true);
			sld.name = "Amelia";
			sld.lastname = "";
			sld.dialog.FileName = "Quest\Mangarosa.c";
			sld.dialog.currentnode = "amelia";
			//sld.greeting = "";
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Amelia_house", "barmen", "stay");
		break;
		
		// --> Тёмные воды исцеления
		case "dwh_ne_ta":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "아니, "+GetSexPhrase("친애하는","아름다움")+", 내가 필요한 사람이 아니오, 그건 "+sld.name+". 그녀는 지금 이 도시에 있어. 최근에 봤어.";
			link.l1 = "감사합니다.";
			link.l1.go = "exit";
		break;
		// <-- Тёмные воды исцеления
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"내 말 좀 들어봐, 용감한 매야. 나는 집시일지라도, 우리조차도 노골적인 폭력은 비난해. 제발 칼을 거둬 줘.","내 말 좀 들어주게, 용감한 매여. 이 마을 시민으로서 자네에게 검을 거두어 달라고 부탁하네.");
			link.l1 = LinkRandPhrase("좋아.","원하시는 대로 하겠습니다.","말씀대로 하겠습니다...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string GuessText()
{
	string sText;
	switch (hrand(19))
	{
		case 0: sText = "you will have luck, brave young falcon, tomorrow you'll be lucky with cards!" break;
		case 1: sText = "the fortune will be kind with you in your mercantile business, captain!" break;
		case 2: sText = "there is a misfortune awaiting you in the open sea, it's waiting just for you, wait for three days!" break;
		case 3: sText = "I see that you need to seek help from your closest ones, you won't make it alone in your next fight!" break;
		case 4: sText = "go and light a candle in a church, you have been cursed by your enemy. You won't make it without God's help!" break;
		case 5: sText = "you are going to lose a lot soon, my falcon, but don't despair and hope for yourself, seek help from you friends..." break;
		case 6: sText = "a heavy loss is waiting for you in the sea, but I see, that you, captain, will be able to ride it out even if you don't get what you want." break;
		case 7: sText = "you have entered the aim of misfortune, captain! Visit a brothel and have some rest." break;
		case 8: sText = "you will get what you want, captain, but don't expect anything good from it. All what you've wanted so passionately, captain, will bring only bad things so you'd better change your plans away." break;
		case 9: sText = "I see that there is a sign on that face of yours, the sign of ultimate luck. You will get more than you're expecting to get, young man!" break;
		case 10: sText = "you need to evaluate your wish once again and decide. Do you really need it? Your fate is giving you a chance to rethink." break;
		case 11: sText = "it's rare luck, not everyday we've getting a chance to rethink. Take a rest for a few days, bright-eyed, think about things. Don't hurry to your death!" break;
		case 12: sText = "though all of your efforts won't give you the expected result, don't despair, young falcon, great luck is waiting for you in the most unexpected day, don't lose it!" break;
		case 13: sText = "your problem won't be solved in a positive way but you are a stubborn one and you'll get what you want but, perhaps, not from the place you've expected." break;
		case 14: sText = "you'd better forget about the business you are up to. You will never be lucky in this and if you'll be continuing in it than, perhaps, your closest people will be hurt or killed." break;
		case 15: sText = "there is an event which is waiting for you, captain, and it will completely change your life. Your recent concerns will lose all of their meaning to you after that." break;
		case 16: sText = "there is danger on your way to your dream, captain, and you must be really lucky if you will be able to get what you want without heavy losses. It's better to turn away and forget your unachievable dream. Or perhaps, this fate could be tricked if you lose in cards or dice right now..." break;
		case 17: sText = "I see a strong power in you like a rock and a light as bright as the north star which leads people. Good news is waiting for you!" break;
		case 18: sText = "a bad sign is rising on your way, fear the evil eye and keep loyal men close to you." break;
		case 19: sText = "a lucky event is rising on your way right behind your own back. Look for the good which is coming right to your hands and don't chase the unachievable." break;
	}
	return sText;
}
