// диалоги персонажей по квесту Мангароса
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
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
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니야.";
			link.l1.go = "exit";
		break;
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = "내 집에 무슨 일로 왔지?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "네 이름이 아멜리아 맞지? 식물에 대해 물어보려고 왔어. 망가 로사.";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "아직 너에게 해줄 말이 없어. 하지만 언젠가 다시 올 거야...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "흥미롭군! 그런데 누가 내 얘기를 해줬지, 용감한 청년?";
			link.l1 = "네 사람 중 한 명이야. 그 여자가 이 식물의 비밀을 알고 있고, 나에게 이걸로 특별한 물약을 만드는 법을 가르쳐줄 수 있다고 했어...";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "우선, 네가 말하는 그 식물을 보여 줘라. 혹시 아무것도 모르면서 내 시간만 낭비하는 건 아니겠지. 네 망가 로사는 어디 있지?";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "여기, 한번 봐.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "음...";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "그리고 뭘 보여주려고 했지? 망가 로사가 없잖아. 그러니까 꺼져, 이봐, 내 인내심이 바닥나기 전에. 이 대화는 끝이다.";
			link.l1 = "하지만...";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "또 너냐? 말썽 부리지 마, 이 녀석...";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "진정해, 아멜리아. 지난번에 내가 어디에선가 떨어뜨렸나 봐. 자, 망가 로사를 가져왔어. 한번 봐봐.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = "그래... 뭔가 알고 있는 것 같군. 내 비약의 비밀을 너한테 알려주길 바라나?";
			link.l1 = "정확해. 그리고 공짜는 아닌 것 같은데...";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "잘 이해했구나, 젊은이! 완전한 바보처럼 보이지는 않는군. 그래, 지식을 구하고 이 귀한 식물을 쓸데없는 흡연 따위에 낭비하지 않는 사람이라면 내가 가르쳐줄 수 있지...";
			link.l1 = "아멜리아, 흥정을 시작하기 전에... 망가 로사로 만들 수 있는 물약에 대해 기본적인 지식을 좀 알려줄 수 있겠소?";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "흥정은 없어, 친구. 내가 값을 말하면, 그걸 지불할지 말지는 네가 결정하는 거야. 깎아주거나 할인해줄 생각하지 마, 여긴 시장이 아니니까. 그리고 네 질문에 대해 말하자면... 망가 로사로 특별한 물약을 만들 수 있는데, 그건 네 신체 능력을 강화해 줄 거야. 더 강해지거나, 더 오래 버티거나, 더 빨라질 수도 있고, 아니면 몸 전체가 변화해서 모든 면에서 강해질 수도 있어. 하지만 그런 물약은 앞의 두 가지보다 효과가 약할 거다.";
			link.l1 = "매우 흥미롭군. 값을 말해봐.";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "내가 너에게 세 가지 조리법을 가르쳐 줄 수 있다네. 각 조리법마다 식물 하나와 금화 오백 닢을 내게 주게.";
			link.l1 = "이 약들에 대해 더 말해 봐. 각각 무슨 효과가 있지?";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "연금술의 대가가 되어야만 물약 하나라도 제대로 만들 수 있지. 각 물약의 효과는 마신 시점에 따라 최대 이틀까지 지속된다네. 한밤중에 마시면 거의 이틀 내내 효과가 가지\n첫 번째 물약은 힘과 체력을 높여준다네. 전투에서 더 잘 싸우고, 덜 다치며, 더 많은 짐을 들 수 있지\n두 번째 물약은 네 몸을 더 빠르고 민첩하게 만들어주고, 지치지 않게 해주며, 명중률도 높여준다네\n세 번째 물약은 앞의 두 물약에 비해 효과가 절반밖에 안 되지만, 매력과 자신감, 그리고 행운까지 얻게 해주지\n모든 만가 로사 기반 물약은 건강에도 좋은 영향을 준다네. 한 번에 하나씩만 마셔야 하고, 절대 섞어 마시지 마라. 그렇지 않으면 아무 효과도 없을 뿐더러, 심각한 중독에 걸릴 거야\n그래, 잘생긴 이여, 지금 바로 그 지식을 살 텐가, 아니면 생각할 시간이 더 필요한가?";
			if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
			{
				link.l1 = "그래, 준비됐어.";
				link.l1.go = "amelia_8";
			}
			link.l2 = "잠깐 생각할 시간이 필요해. 이건 큰 결정을 내려야 하거든.";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (!CheckAttribute(npchar, "quest.ChickenGod") && CheckCharacterItem(pchar, "talisman11")) {
				if (CheckAttribute(npchar, "quest.recipe_power") || CheckAttribute(npchar, "quest.recipe_fast") || CheckAttribute(npchar, "quest.recipe_total")) {
					link.chickengod = "Amelia, you seem to have a knack for such things. Can you tell me if there is a demand for such stones among your people? I find them everywhere - it's like everyone is obsessed with them!";
					link.chickengod.go = "chickengod";
				}
			}
			
			if (CheckAttribute(npchar, "quest.ChickenGod") && !CheckAttribute(npchar, "quest.ChickenGod.Complete") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.chickengod = "Here you go, Amelia. Just as you ordered: one hundred and thirteen adder stones.";
				link.chickengod.go = "chickengod_collected";
			}
		
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "아, 너였구나, 젊은이! 자, 내 약이 도움이 되었나?";
				link.l1 = "정말 그랬어, Amelia. 고마워!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "아, 너구나, 젊은이! 레시피 좀 사볼래?";
				if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
				{
					link.l1 = "맞아. 그래서 내가 여기 온 거야.";
					link.l1.go = "amelia_8";
				}
				
				link.l2 = "아직 아니야, Amelia. 그냥 들렀을 뿐이야.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "좋아. 어떤 종류의 조리법을 사고 싶은가?";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "힘과 인내의 물약 조제법.";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "민첩함과 지치지 않는 힘의 물약 조제법.";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "복잡한 물약의 조제법.";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "좋아. 나는 그것을 '해일'이라고 이름 지었어. 자, 설명서를 가져가. 잘 읽어봐. 그리고 제대로 사용하는 법을 잊지 마!";
			link.l1 = "감사합니다, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "좋아. 이름은 '스콜'로 지었어. 자, 설명서를 가져가. 잘 읽어봐. 그리고 제대로 쓰는 법 잊지 마!";
			link.l1 = "고마워, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "좋아. 이름은 '바다의 포옹'이라고 지었어. 자, 이 설명서를 가져가. 잘 읽어봐. 그리고 제대로 사용하는 법을 잊지 마!";
			link.l1 = "감사합니다, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveDublonsFromPCharTotal(500);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info("You have given 500 doubloons and one Manga Rosa");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
		
		case "chickengod":
			dialog.text = "Bax de adder라니, 정말이지! 별로 값어치는 없지만, 아는 사람에겐 쓸모가 있지. 그걸 113개 가져오면 내 보물상자 하나를 열어주지.";
			link.l1 = "저게 다 돌덩이 더미잖아! 먼저 왜 그게 필요한지 말해보지 그래?";
			link.l1.go = "chickengod_1";
		break;
		
		case "chickengod_1":
			dialog.text = "아니야, 자기야, 물어봐야 할 정도라면 아직 이 지식은 너한테 쓸모없어.";
			link.l1 = "그렇게 후하게 열어주겠다고 약속한 그 상자 안에는 뭐가 들어 있지?";
			link.l1.go = "chickengod_2";
		break;
		
		case "chickengod_2":
			dialog.text = "선장이라도 손수 일하는 걸 마다하지 않는 이들에게 쓸모 있는 게 아주 많지. 내 시간 낭비하지 마, 자기야, 어차피 그 많은 조약돌은 못 주워.";
			link.l1 = "그건 두고 보자!";
			link.l1.go = "exit";
			
			npchar.quest.ChickenGod = true;
		break;
		
		case "chickengod_collected":
			dialog.text = "하하하! 농담이었어, 자기야!";
			link.l1 = "네가 네 오두막에서 불타 죽을 때, 그때야말로 네가 웃음거리가 될 거다, 마녀!";
			link.l1.go = "chickengod_collected_1";
		break;
		
		case "chickengod_collected_1":
			dialog.text = "그게 내 운명은 아니야, 자네... 자네 덕분에 이 집시가 자랑스럽구나! 자, 이 상자는 자네가 마음껏 가져가도 돼.";
			link.l1 = "고마워, 아멜리아. 그런데 네 낡은 속옷 말고 쓸 만한 게 좀 들어 있길 바란다...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			npchar.quest.ChickenGod.Complete = true;
			AddDialogExitQuestFunction("ChickenGod_AmeliaOpenChest");
		break;
	}
} 
