void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "그건 확실히 버그야. 언제, 어떻게 그런 일이 일어났는지 제이슨에게 꼭 알려줄 수 있겠어?";
			link.l1 = "알겠어.";
			link.l1.go = "exit";
		break;
		
		// шаман карибов Туттуатхапак
		case "Tuttuat":
			dialog.text = "왜 내 오두막에 왔지, 백인? 투투아타팍은 너를 소중한 손님이라 생각하지 않는다.";
			if (GetCharacterFreeItem(pchar, "mushket1") || GetCharacterFreeItem(pchar, "mushket2") || GetCharacterFreeItem(pchar, "mushket7"))
			{
				link.l1 = "위대한 투투아타파크 주술사님, 안녕하십니까. 저는 당신의 도움과 조언을 구하러 왔습니다. 제 선의의 표시로 이 머스킷을 받아 주십시오.";
				link.l1.go = "Tuttuat_1";
			}
			else
			{
				link.l1 = "위대한 투투아타파크 주술사님, 안녕하십니까. 저는 당신의 도움과 조언을 구하러 왔습니다.";
				link.l1.go = "Tuttuat_exit";
			}
		break;
		
		case "Tuttuat_exit":
			dialog.text = "투투아타팍은 백인을 돕지 않는다. 백인들은 나쁜 놈들이다. 그들은 인디언을 죽이고 정복하며, 인디언을 노예로 만든다. 투투아타팍은 백인에게 아무 조언도 주지 않는다. 이제 나가라.";
			link.l1 = "흠...";
			link.l1.go = "Tuttuat_exit_1";
		break;
		
		case "Tuttuat_exit_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat";
		break;
		
		case "Tuttuat_1":
			if (GetCharacterFreeItem(pchar, "mushket1")) 
			{
				sTemp = "mushket1";
			}
			else 
			{
				if(GetCharacterFreeItem(pchar, "mushket2"))
				{
					sTemp = "mushket2";
				}
				else
				{
					sTemp = "mushket7";
				}
			}
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			Log_Info("You have given: "+XI_ConvertString(sTemp)+"");
			dialog.text = "너, 투투아타팍에게 무엇을 줘야 하는지 알지, 백인. 투투아타팍은 네 선물을 받겠다. 이제 말하마. 내게서 어떤 조언을 구하느냐?";
			link.l1 = "남쪽 먼 곳에서 왔다고 들었소. 나는 인디언 부적을 가지고 있는데, 어떤 박식한 사람이 자네라면 이걸 어떻게 쓸 수 있는지 알지도 모른다고 하더군.";
			link.l1.go = "Tuttuat_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_2":
			dialog.text = "부적을 보여 줘.";
			link.l1 = "여기 있습니다, 위대한 주술사님.";
			link.l1.go = "Tuttuat_3";
		break;
		
		case "Tuttuat_3":
			PlaySound("interface\important_item.wav");
			dialog.text = "(부적을 바라보며)... 네 친구 말이 맞다, 백인. 이 부적은 내 민족, 위대한 인디언들에게 속한 것이었지. 차빈이라 불렸던 이들이네. 저주받고 신성모독을 일삼는 창백한 놈이 성소를 더럽히고 이걸 여기로 가져왔지. 투투아타팍께서 그 놈을 벌하셨다.";
			link.l1 = "그 자의 정신을 빼앗은 건 자네인가?";
			link.l1.go = "Tuttuat_4";
		break;
		
		case "Tuttuat_4":
			dialog.text = "백인이 그 지식을 보여주어 투투아타파크를 놀라게 한다. 그래, 나는 그 더러운 놈의 정신을 집어삼켰지. 그 자와 그의 추잡한 졸개들은 마땅한 대가를 치렀다.";
			link.l1 = "그렇군... 주술사여, 이 부적은 무엇에 쓰는 것이오? 혹시 전투에서 몸을 지키거나 사악한 마법을 막아주는 것인가?";
			link.l1.go = "Tuttuat_5";
		break;
		
		case "Tuttuat_5":
			dialog.text = "이 부적은 너한테 아무 소용 없어, 백인 선장. 너는 이 힘을 쓸 수 없지. 우리 부족의 위대한 주술사들만이 그 힘을 깨울 줄 안다.";
			link.l1 = "흠... 결국 이렇게 긴 여정을 헛되이 한 셈이군. 하지만 혹시 이 부적의 힘을 깨울 수 있겠소, 위대한 주술사? 우리 서로 합의할 수 있지 않겠소...\n";
			link.l1.go = "Tuttuat_6";
		break;
		
		case "Tuttuat_6":
			dialog.text = "내가 부적을 깨운다 해도, 너는 그 힘을 오래 가지지 못할 거다. 하지만 거래를 제안하지, 백인 놈아.";
			link.l1 = "무슨 거래인데?";
			link.l1.go = "Tuttuat_7";
		break;
		
		case "Tuttuat_7":
			dialog.text = "이런 부적 세 개가 우리 신전에서 도난당했다네. 각각 다른 힘을 지니고 있지만, 모두 모이면 아주, 아주 강력해지지. 세 개의 부적을 모두 찾아서 내게 가져오면 보상을 주겠네. 영원히 간직할 수 있는 힘을 주겠네.";
			link.l1 = "잘 이해가 안 되는데... 무슨 힘을 말하는 거지?";
			link.l1.go = "Tuttuat_8";
		break;
		
		case "Tuttuat_8":
			dialog.text = "때가 되면 모든 것을 알게 될 것이다. 세 개의 부적을 모두 찾아서 내게 가져오너라. 그 부적들은 카리브 해에 있다. 찾아내서 가져오너라. 쉽게 알아볼 수 있을 것이다 – 서로 비슷하게 생겼으니. 가거라, 백인. 투투아타팍이 기다리며, 영혼들에게 네게 힘을 달라고 빌고 있다.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_9";
		break;
		
		case "Tuttuat_9":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "ghostship"; 
			AddQuestRecord("Caleuche", "3");
			pchar.quest.Caleuche_ghostship.win_condition.l1 = "location";
			pchar.quest.Caleuche_ghostship.win_condition.l1.location = "Dominica";
			pchar.quest.Caleuche_ghostship.function = "Caleuche_PrepareGhostship";
		break;
		
		case "Tuttuat_10":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "가라, 백인 놈. 부적 두 개 더 찾아와라.";
				link.l1 = "이미 찾았소, 위대한 주술사님. 여기, 한번 보시오.";
				link.l1.go = "Tuttuat_33";
			}
			else
			{
				dialog.text = "가라, 백인. 나머지 두 개의 부적을 찾아라.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_10_1";
			}
		break;
		
		case "Tuttuat_10_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_10";
		break;
		
		case "Tuttuat_11":
			dialog.text = "또 왔나, 백인? 정글에서 사나운 재규어라도 만난 얼굴이군.";
			link.l1 = "더 심각합니다, 위대한 주술사님. 제가 바다에 들어서자마자 어디선가 거대한 폭풍이 몰아쳤고, 언데드들이 조종하는 배가 저를 공격해 왔습니다! 그들의 선장은 완전히 무적이었습니다. 먼저 그가 제게서 부적을 빼앗고 거의 저를 죽일 뻔했지요 – 간신히 살아남았습니다. 그리고 나서 그들은 제 배를 거의 침몰시켰고, 제 선원들 중 극소수만 살아남았습니다.";
			link.l1.go = "Tuttuat_12";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_12":
			dialog.text = "나쁜 소식이야, 백인 놈. 칼레우체가 다시 공격하러 온다네.";
			link.l1 = "칼레우체? 그 언데드 선장은 자기 배를 플라잉 하트라고 불렀지. 그러니까, 유령선에 대해 알고 있었으면서도 나한텐 말 안 했던 거야? 만약 저 떠도는 악몽이 부적을 노리고 있다는 걸 알았더라면, 난 절대로...";
			link.l1.go = "Tuttuat_13";
		break;
		
		case "Tuttuat_13":
			dialog.text = "투투아타팍은 백인 선장이 화가 난 걸 본다. 백인 선장은 진정해야 한다.";
			link.l1 = "진정하라고?! 미쳤어? 내가 그런 걸 상대로 어떻게 살아남겠어!";
			link.l1.go = "Tuttuat_14";
		break;
		
		case "Tuttuat_14":
			dialog.text = "그래. 진정하고 소리 지르지 마라. 말해 봐라 – 아직도 내게서 영원히 함께할 큰 힘을 받고 싶으냐?";
			link.l1 = "그야, 당연히 알지. 하지만 이제 부적은 없어.";
			link.l1.go = "Tuttuat_15";
		break;
		
		case "Tuttuat_15":
			dialog.text = "내가 카레우체 선장에게서 부적을 빼앗는 방법을 가르쳐주지. 쉽지는 않을 거야.\n하지만 해낸다면, 그 자의 배를 전리품으로 차지하고, 값진 보물을 찾고, 네 동료들 사이에서 명성을 얻으며, 내게서도 보상을 받을 수 있을 거다.";
			link.l1 = "젠장! 저 쭈글쭈글한 괴물을 당장이라도 박살내고 싶다!\n하지만 칼도 총도 안 통하는 놈을 내가 어떻게 이기란 말이냐?!";
			link.l1.go = "Tuttuat_16";
		break;
		
		case "Tuttuat_16":
			dialog.text = "내 말 들을 준비 됐나, 백인 선장?";
			link.l1 = "그래, 맞아, 위대한 주술사님.";
			link.l1.go = "Tuttuat_17";
		break;
		
		case "Tuttuat_17":
			dialog.text = "내 아버지가 젊은 전사였을 때, 백인들이 플라잉 하트라는 배를 타고 우리 땅에 왔다. 그들은 산으로 갔다. 전설에 따르면, 그곳에는 우리 조상들의 신전이 숨겨져 있다고 한다. 재규어 전사들의 신전이지. 백인들은 신전과 황금을 찾아냈고, 고대의 신성한 것을 더럽혔다. 그들은 차빈족의 위대한 보물, 죽음의 신이자 재규어 전사들의 수호신인 윰 시밀의 옥 해골을 가져갔다.\n백인들은 다시 배로 돌아갔다. 그들은 더 많은 황금을 얻으려고 돌아오기로 했지만, 그들 중 한 명이 땅에 발을 딛는 순간 끔찍한 고통 속에 죽었다. 윰 시밀이 선장과 선원들에게 저주를 내린 것이다. 그들은 불멸이 되었지만 다시는 땅을 밟을 수 없게 되었다. 그들은 아주 오랜 겨울 동안, 네 달력으로는 반세기 동안 바다를 떠돌았다. 그렇게 칼레우체가 탄생했다.\n그들의 몸은 시들고, 살은 썩었지만 여전히 살아 있었다. 팔이나 다리를 잘라도 다시 자라나고, 몸을 반으로 갈라도 다시 온전해진다. 그들의 배가 침몰해도 물속에서 고쳐 다시 항해한다.";
			link.l1 = "정말 끝내주네...";
			link.l1.go = "Tuttuat_18";
		break;
		
		case "Tuttuat_18":
			dialog.text = " 칼레우체는 선원들을 공포에 몰아넣지. 아무 이유 없이 공격해서, 나타나면 반드시 죽음이 따라온다네. 카리브 해에서는 자주 보이지 않지만, 내 고향 해안가를 따라 항해하는 걸 더 좋아하지. 내 생각엔 저주를 풀고 싶은 모양이야. 하지만 절대 풀지 못할 거다네.";
			link.l1 = "왜? 저주를 풀려면 무엇을 해야 하지?";
			link.l1.go = "Tuttuat_19";
		break;
		
		case "Tuttuat_19":
			dialog.text = "옥 해골이다. 이것은 재규어 전사들의 신전, 윰 시밀의 사당에 돌려놓아야 해. 신전이 여러 군데 있지. 우리 부족의 장로들은 카리브 해의 작은 섬에 하나 있다고 말씀하셨다네.\n그래서 칼레우체가 그리로 항해한 거야. 해골이 신전에 놓이면 윰 시밀의 마법이 깨지고, 그들은 필멸의 존재가 되어 더 이상 상처를 치유할 수 없게 되지.";
			link.l1 = "하! 차라리 해골을 돌려주지 않을 가능성이 더 크지! 불멸이고 무적이라면 굳이 돌려줄 이유가 없잖아? 게다가, 땅에 발을 디딜 수 없다면 애초에 해골을 가져올 수도 없지, 안 그래?";
			link.l1.go = "Tuttuat_20";
		break;
		
		case "Tuttuat_20":
			dialog.text = "그들은 해골을 가지고 있지 않아. 선장이 재규어 인간들의 성소에서 돌아왔을 때, 내 조상들의 땅에 그걸 버렸지. 옥은 금이 아니니까, 백인들은 필요 없었고, 해골의 눈에서 아름다운 초록 보석을 가져갈 수도 없었어. 그래서 그냥 버렸지. 한 선원이 그걸 주웠는데, 저주는 그를 건드리지 않았어\n그 선원이 칼레우체 선원들이 어떻게 변했는지 보고는 도망쳤어. 우리 마을로 왔지. 내 아버지가 그 선원과 윰 시밀의 해골을 봤어. 그리고 그 백인은 해골을 가지고 해안을 따라 북쪽으로 갔지.";
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul"))
				{
					link.l1 = "초록색 보석이 박힌 옥 해골 말인가? 내가 직접 손에 쥐어봤다니까, 상상이 가나? 내가 솔로몬한테 직접 넘겼지. 그런데 그가 딸과 함께 유럽으로 떠났고, 해골도 가져간 것 같더군.";
				}
				else
				{
					link.l1 = "눈구멍에 녹색 보석이 박힌 비취 해골? 젠장... 나... 내가 그걸 직접 손에 들었었어! 그리고 어떤 포르투갈 놈한테 팔았지... 메리먼인가, 뭐 그런 이름이었어... 그래, 그가 그렇게 불렀어 - 윰 시밀의 해골이라고! 그놈, 그걸 미친 듯이 원했어! 무려 50만 페소나 주고 샀다니까!";
				}
				link.l1.go = "Tuttuat_21_1";
			}
			else
			{
				link.l1 = "초록 보석이 박힌 옥 해골이라니? 그걸 내가 찾아야 한다는 거야? 하지만 그 선원은 오십 년 전에 셀바에서 죽었을 수도 있고, 해골도 영영 사라졌을지 몰라!";
				link.l1.go = "Tuttuat_21_2";
			}
		break;
		
		case "Tuttuat_21_1":
			dialog.text = "나는 해골이 카리브 해에 있다는 걸 알고 있지. 칼레우체가 여기 있는 건 우연이 아니야.\n지난 여섯 달 동안 그 배가 그 섬 근처에서 자주 목격됐어.\n예전에는 많은 겨울 동안 그곳에 없었지.\n칼레우체의 선장은 재규어 전사의 유물을 감지할 수 있어. 그래서 네 배와 너를 찾아낸 거야.";
			link.l1 = "그럼, 내가 이 해골을 다시 찾아야 한다는 말이지? 그리고 나서 그걸로 뭘 해야 하는 거야?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_21_2":
			dialog.text = "해골은 분명 여기, 카리브 해에 있어. 칼레우체가 여기 있는 것도 우연이 아니지. 지난 여섯 달 동안 그 배가 그 섬에서 자주 목격됐어. 그 전에는 여러 해 동안 거기 없었지. 칼레우체의 선장은 재규어 인간들의 유물을 감지할 수 있어. 그래서 그가 너와 네 배를 찾아낸 거야.";
			link.l1 = "그러니까, 내가 다시 그 해골을 찾아야 한다는 말이지? 그 다음엔 그걸로 뭘 해야 하는 거야?";
			link.l1.go = "Tuttuat_22";
		break;
		
		case "Tuttuat_22":
			dialog.text = "먼저, 우리가 말했던 두 개의 부적을 찾아야 해. 그것들이 없으면 아무것도 할 수 없어. 부적이 있어야 재규어 인간들이나 마주치는 어떤 적과도 맞설 힘을 얻을 수 있지.";
			link.l1 = "재규어 인간들과 맞서 싸우라고? 무슨 소리를 하는 거야?";
			link.l1.go = "Tuttuat_23";
		break;
		
		case "Tuttuat_23":
			dialog.text = "네가 옥 해골을 가져가야 할 사원은 카리브 해의 무인도에 있다. 그곳은 재규어 인간들이 지키고 있지. 그들은 모두 죽었었지만, 이제 다시 살아났지. 부적 없이는 그들을 통과할 수 없을 거다.\n살아 있을 때 재규어 인간들은 사나운 전사였고, 죽어서 거의 무적이 되어버렸다. 그들에게 힘을 주는 이는 바로 윰 시밀이다.";
			link.l1 = "언데드? 또야? 운도 지지리 없군...";
			link.l1.go = "Tuttuat_24";
		break;
		
		case "Tuttuat_24":
			dialog.text = "왜 그렇게 놀라는 거지, 백인 선장? 움 시밀은 죽음의 신이야, 비취 해골은 죽은 자와 산 자를 지배하는 힘을 준다네. 카리브해. 재규어 인간들이 그것을 지키고 있지. 부적 없이는 그들을 통과할 수 없어. 부적이 있으면 신전에 들어가 살아남을 수 있고, 해골을 거기에 두고 나서 칼레우체를 찾아가 그녀의 선장을 쓰러뜨리고 네게서 빼앗아간 부적을 되찾을 수 있지.";
			link.l1 = "그런데 카레우체 선장은 왜 이 부적들이 필요한 거지?";
			link.l1.go = "Tuttuat_25";
		break;
		
		case "Tuttuat_25":
			dialog.text = "내 생각엔 그가 재규어 전사들의 신전으로 가고 싶어 하는 것 같아, 그리고 그 부적이 도움이 될 거라 믿는 모양이야. 하지만 내가 틀렸을 수도 있지. 그래도 칼레우체는 언제나 내 고향의 유물에 이끌리거든. 그녀는 재규어 전사들의 신전이 있는 섬 근처를 항해했고, 내 조국 해안도 따라 항해했어.";
			link.l1 = "그 섬은 어디에 있지?";
			link.l1.go = "Tuttuat_26";
		break;
		
		case "Tuttuat_26":
			dialog.text = "먼저 유므 시밀의 해골과 부적들을 찾아. 그다음에 섬에 대해 이야기하지.";
			link.l1 = "좋아. 옥 해골을 어디서 찾아야 할지 힌트 좀 줄 수 있겠어?";
			link.l1.go = "Tuttuat_27";
		break;
		
		case "Tuttuat_27":
			dialog.text = "모르겠어. 하지만 여기, 카리브에 있어. 부적도 마찬가지야. 물어봐. 찾아봐. 찾아내.";
			link.l1 = "헤... 좋아, 해볼게.";
			link.l1.go = "Tuttuat_28";
		break;
		
		case "Tuttuat_28":
			dialog.text = "그리고 너도 조심해라, 백인 선장. 칼레우체는 차빈의 물건을 감지한다. 부적을 가지게 되면, 그녀가 널 찾아올 거다. 그녀가 널 찾으면, 도망쳐라, 빨리. 만약 잡히면, 넌 죽은 목숨이다.";
			link.l1 = "이 빌어먹을 배, 미친 듯이 빠르군! 내가 본 어떤 배보다도 두 배는 빠른 것 같아. 하지만 바람을 맞받아 항해할 때는 힘들어하는 걸 봤지.";
			link.l1.go = "Tuttuat_29";
		break;
		
		case "Tuttuat_29":
			dialog.text = "칼레우체는 저주받은 배야 - 그래서 그렇게 빠른 거지. 도망치기 힘들어. 칼레우체보다 더 빠른 배가 있어야 해. 아니면 죽게 될 거야. 부적을 찾으면 내게 가져와. 부적을 배에 두지 마라.";
			link.l1 = "이미 받았소. 이야기 들려줘서 고맙소, 위대한 주술사여. 이제 나는 가야겠군.";
			link.l1.go = "Tuttuat_31";
		break;
		
		case "Tuttuat_31":
			dialog.text = "나는 영혼들에게 네게 힘을 주고 칼레우체에게서 구해 달라고 기도하고 있다.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_32";
		break;
		
		case "Tuttuat_32":
			DialogExit();
			LocatorReloadEnterDisable("Shore27", "boat", false);
			npchar.dialog.currentnode = "Tuttuat_10";
			pchar.questTemp.Caleuche = "mayak"; 
			AddQuestRecord("Caleuche", "6");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "Santiago_Lightman") {AddLandQuestMark(characterFromId("Santiago_Lightman"), "questmarkmain");}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Amuletmaster") && pchar.questTemp.Caleuche.Amuletmaster == "BasTer_Lightman") {AddLandQuestMark(characterFromId("BasTer_Lightman"), "questmarkmain");}
		break;
		
		case "Tuttuat_33":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(살펴보며) 그래, 그거야. 두 번째 차빈 부적이지. 잘했군. 하지만 아직 부적 하나를 더 찾아야 해.";
			link.l1 = "그거 기억하고 있소, 주술사. 곧 갖게 될 거요.";
			link.l1.go = "Tuttuat_34";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_34":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
			AddQuestRecord("Caleuche", "22");
			if (!Caleuche_CheckAmulet())
			{
				if (GetCharacterIndex("Map_Caleuche") != -1)
				{
					sld = characterFromId("Map_Caleuche");
					sld.lifeday = 0;
					Map_ReleaseQuestEncounter("Map_Caleuche");
				}
			}
		break;
		
		case "Tuttuat_35":
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && Caleuche_CheckAmulet())
			{
				dialog.text = "가라, 백인 놈. 부적 하나 더 찾아와라.";
				link.l1 = "이미 가지고 있어, 위대한 주술사. 여기, 한번 봐.";
				link.l1.go = "Tuttuat_36";
			}
			else
			{
				dialog.text = "가라, 백인 놈. 부적 하나 더 찾아와라.";
				link.l1 = "...";
				link.l1.go = "Tuttuat_35_1";
			}
		break;
		
		case "Tuttuat_35_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_35";
		break;
		
		case "Tuttuat_36":
			if (CheckCharacterItem(pchar, "kaleuche_amulet2")) RemoveItems(pchar, "kaleuche_amulet2", 1);
			else RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given the amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "(살펴보며) 그래, 바로 저거야. 세 번째 차빈스 부적이지. 잘했어. 죽은 재규어 전사들, 윰 시밀의 하인들을 통과하려면 모든 부적을 찾아야 했거든.";
			link.l1 = "이제 보아하니, 내가 비취 해골이 필요하겠군?";
			link.l1.go = "Tuttuat_37";
			DelLandQuestMark(npchar);
			DelMapQuestMarkIsland("Dominica");
		break;
		
		case "Tuttuat_37":
			dialog.text = "네 말이 옳다. 윰 시밀의 비취 해골이야. 그걸 차빈의 신전에 가져가야 해. 그러면 칼레우체의 힘이 영원히 사라질 거다.";
			link.l1 = "투투아타팍, 제발, 어디를 찾아봐야 할지 말해 줘. 생각나는 거 있어?";
			link.l1.go = "Tuttuat_38";
		break;
		
		case "Tuttuat_38":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "아니. 마지막으로 옥 해골을 본 곳을 생각해 봐. 누구에게 줬는지도. 거기서부터 찾아봐.";
				link.l1 = "알겠소, 위대한 주술사. 내가 할 수 있는 건 다 해보겠소.";
				link.l1.go = "Tuttuat_39";
			}
			else
			{
				dialog.text = "유믹 시밀의 해골에 관심이 있는 백인 주술사가 있소. 그 자가 해골을 찾고 있지. 우리 마을까지 찾아왔었네. 그 주술사는 네덜란드 섬의 어느 집에 산다고 들었소. 네덜란드 섬에서 그 주술사를 찾아보면 뭔가 알 수 있을 것이오.";
				link.l1 = "알겠소, 위대한 주술사. 내가 할 수 있는 건 모두 해보겠소.";
				link.l1.go = "Tuttuat_39";
			}
		break;
		
		case "Tuttuat_39":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
			AddQuestRecord("Caleuche", "23");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "I'll start with Curacao, where I handed it over to Solomon. Maybe I'll find some clue - to find out what happened to the skull.";
				else sTemp = "I'll start with visiting Curacao - there I've sold the jade skull to Joachim Merriman.";
			}
			else sTemp = "Tuttuathapak told me, that a 'white warlock' showed interest in the jade skull, and adviced seeking for him on Dutch islands. Who might that be?";
			AddQuestUserData("Caleuche", "sText", sTemp);
			if (GetCharacterIndex("Map_Caleuche") != -1)
			{
				sld = characterFromId("Map_Caleuche");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter("Map_Caleuche");
			}
			pchar.questTemp.Caleuche = "skul";
			pchar.quest.Caleuche_villemstad.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstad.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Caleuche_villemstad.function = "Caleuche_CreateMonk";
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Tuttuat_40":
			dialog.text = "가라, 백인 놈. 윰 시밀의 비취 해골을 찾아라.";
			if (pchar.questTemp.Caleuche == "island")
			{
				link.l1 = "여기 있어, 위대한 주술사 나리, 한번 보시지.";
				link.l1.go = "Tuttuat_45";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "Tuttuat_40_1";
			}
		break;
		
		case "Tuttuat_40_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_41":
			dialog.text = "가라, 백인 놈. 윰 시밀의 비취 해골을 찾아라.";
			link.l1 = "미안하지만 나는 그 일을 할 수 없을 것 같아. 흑마법사를 찾긴 했는데, 마지막 순간에 해골을 들고 도망쳤어. 지금 그가 어디에 있을지 전혀 모르겠어.";
			link.l1.go = "Tuttuat_42";
		break;
		
		case "Tuttuat_42":
			dialog.text = "이거 아주 나쁘다, 백인 놈. 이제 너는 사원을 통과하지도 못하고 칼레우체도 이기지 못할 거다. 나는 너에게 아무런 선물도 주지 않는다. 이제 나가라.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_43";
		break;
		
		case "Tuttuat_43":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_44";
		break;
		
		case "Tuttuat_44":
			dialog.text = "이제 나가, 백인 놈.";
			link.l1 = "...";
			link.l1.go = "Tuttuat_44_1";
		break;
		
		case "Tuttuat_44_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_40";
		break;
		
		case "Tuttuat_45":
			dialog.text = "(쳐다보며) 그래, 저거야. 정말 아름답군. 그리고 정말 무섭기도 하지.";
			link.l1 = "그래... 하지만 더 흥미로운 건, 내가 쿠바에서 도미니카까지 카리브 해 전체를 건넜을 때는 이 해골을 가지고 있었는데도 칼레우체가 나를 공격하려 들지 않았고, 심지어 보지도 못했다는 거야. 그런데 너한테 부적을 가져갈 때는, 내가 출항하자마자 몇 시간도 안 돼서 계속 쫓아왔지.";
			link.l1.go = "Tuttuat_46a";
			DelLandQuestMark(npchar);
		break;
		
		case "Tuttuat_46a":
			dialog.text = "내 생각엔 칼레우체가 해골을 두려워하거나, 아니면 그 존재를 감지하지 못하는 것 같아. 달리 설명할 방법이 없어. 어쩌면 윰 시밀이 옥 해골을 칼레우체에게 아주 위험하게 만들어 놓았는지도 몰라, 저주에 더해서 말이야. 그래서 선장이 우리 부족의 부적 세 개를 그토록 갖고 싶어했던 걸지도 모르지. 윰 시밀의 주문을 다루는 지혜를 얻으려고 말이야.";
			link.l1 = "그럼, 내 배에 비취 해골이 있는 한, 칼레우체의 공격을 두려워할 필요가 없다는 거지?";
			link.l1.go = "Tuttuat_46b";
		break;
		
		case "Tuttuat_46b":
			dialog.text = "그래, 창백한 얼굴 놈. 네 눈으로 직접 봤잖아.";
			link.l1 = "아주 좋아! 이제 나는 대형 선박의 지휘를 맡고, 괜찮은 선원들을 고용해서, 저 산 자 같은 시체가 마법에서 풀려날 때 멋진 환영을 준비할 수 있겠군. 그자가 나를 미리 가로챌까 봐 두려워할 필요도 없고...";
			link.l1.go = "Tuttuat_46c";
		break;
		
		case "Tuttuat_46c":
			dialog.text = "";
			link.l1 = "...그 주문 말인데, 그나저나 옥 해골은 어디로 가져가야 하지?";
			link.l1.go = "Tuttuat_46";
		break;
		
		case "Tuttuat_46":
			dialog.text = "그걸 차빈의 신전으로 가져가서 네 여정을 끝내야 해. 내가 이야기를 하나 해주고 싶어. 들을 준비 됐나, 백인?";
			link.l1 = "네 지혜라면 언제든 들을 준비가 되어 있소, Tuttuathapak.";
			link.l1.go = "Tuttuat_47";
		break;
		
		case "Tuttuat_47":
			dialog.text = "내 조상들의 전설에 따르면, 아주 오래 전, 창백한 얼굴의 사람들이 아직 우리 땅에 오지 않았을 때, 차빈족의 위대한 추장이 아주 아주 큰 카누를 만들고 전사들과 함께 많은 섬의 땅으로 보냈다고 한다. 위대한 추장의 아들이 그들을 이끌었고, 그들 중에는 고위 샤먼도 한 명 있었다. 많은 섬의 땅에서 그들은 사람이 없는 곳을 발견하고 정착지를 세웠으며, 오직 우리 위대한 조상들만이 지을 수 있었던 윰 시밀을 위한 거대한 사원을 세웠다\n전령들이 좋은 소식을 가지고 돌아왔지만, 아무도 다시는 추장의 아들이나 샤먼, 전사들을 본 적이 없었다. 전설에 따르면 그들이 그곳에 남아 살았다고 하지만, 가장 현명한 샤먼이 영혼들과 교감하며 말하길, 그곳에는 더 이상 사람들이 살지 않고 윰 시밀이 이 땅을 다스린다고 했다\n많은 섬의 땅은 카리브해다, 백인아. 윰 시밀의 사원은 백인도 인디언도 살지 않는 섬에 있다. 오직 윰 시밀의 하인들, 차비나비만이 아직도 사원의 복도를 지키고 있다.";
			link.l1 = "그 섬이 어디에 있지?";
			link.l1.go = "Tuttuat_48";
		break;
		
		case "Tuttuat_48":
			dialog.text = "내가 들은 이야기로는, 그곳은 작은 섬인데, 이 마을이 있는 섬에서 창백한 얼굴들이 '북쪽'이라 부르는 방향에 있고, 세 개의 섬 사이 한가운데에 있으며, 네 번째 쪽에는 거대한 물, 즉 바다가 있다고 하더군.";
			link.l1 = "흠... 도미니카 북쪽, 섬 셋이 삼각형을 이루는 바다 끝자락이라고? 젠장, 그건 엄청 넓은 바다잖아! 아무도 들어본 적 없는 작은 섬을 거기서 어떻게 찾으란 말이야?\n";
			link.l1.go = "Tuttuat_49";
		break;
		
		case "Tuttuat_49":
			dialog.text = "확실히 말할 수는 없네. 하지만 또 다른 이야기를 알고 있지. 네 형제들에게서 들었을 수도 있겠군. 약 스무 해 전, 한 백인이 그 섬을 발견했어. 여자와 노인과 함께, 그는 윰 시밀의 신전에 들어가 강력한 유물, 즉 떠오르는 태양의 오브를 가져갔지. 섬의 해안에서, 창백한 얼굴의 선장은 칼레우체에게 습격당했네\n그 창백한 사내는 영리했어. 그는 떠오르는 태양으로 칼레우체의 선장과 선원들의 시야를 빼앗았지. 칼레우체의 저주가 약해졌고, 선장은 그것을 침몰시켰지만 떠오르는 태양의 오브는 사라져버렸어. 만약 네가 그 창백한 사내를 찾는다면, 그가 그 섬이 어디 있는지 말해줄 거야.";
			if (CheckAttribute(pchar, "questTemp.NatanStory")) link.l1 = "하! 그 '창백한 얼굴의 사내' 내가 누군지 알 것 같군... 이야기가 너무 비슷하잖아. 그래서, 칼레우체가 침몰했다는 거야?";
			else link.l1 = "흠... 그래서, 칼레우체가 침몰했다는 건가?";
			link.l1.go = "Tuttuat_50";
		break;
		
		case "Tuttuat_50":
			dialog.text = "그래, 하지만 저주가 그들을 죽음으로부터 지켜주지. 놈들은 그걸 고치고 영원한 항해를 계속했어.";
			link.l1 = "알겠어. 그런데 사원에서는 뭘 해야 하지? 해골은 어디에 두면 돼? 그걸 지키는 재규어 전사들은 어떻게 이겨야 하지? 만약 그들이 그 주술사 메리먼이 불러낸 것처럼 차비나비라면, 혼자 거기 가는 건 어리석은 짓이야 – 놈들 하나하나가 병사 열 명만큼 강하거든.";
			link.l1.go = "Tuttuat_51";
		break;
		
		case "Tuttuat_51":
			dialog.text = "그렇지 않아. 해골을 든 백인 주술사가 소환한 차비나비들은 약해. 윰 시밀 본인이 소환한 것들보다 훨씬 약하지. 너는 절대 그들에게 상처를 입힐 수 없고, 그들의 무기에 한 번만 닿아도 죽게 돼.";
			link.l1 = "잠깐만 - 그런데 그 '창백한 얼굴의 남자'는 어떻게 사원에 들어가서 유물을 훔칠 수 있었지?";
			link.l1.go = "Tuttuat_52";
		break;
		
		case "Tuttuat_52":
			dialog.text = "처음 그 창백한 얼굴의 사내가 신전에 들어오기 전에는, 죽은 조상들의 영혼이 신전을 지키고 있었지. 그 창백한 사내는 강한 전사였고, 그들을 물리쳤어. 떠오르는 태양의 구슬을 훔쳐갔을 때, 윰 시밀이 크게 분노했지. 그는 그 사내에게 불과 유황을 내렸고 신전을 거의 파괴했지만, 그 사내는 유물을 가지고 도망쳤어. 이제 윰 시밀이 신전을 지키기 위해 무적의 재규어 전사들을 소환했지.";
			link.l1 = "영광스럽군! 그런데 내가 도대체 어떻게 몰래 들어가란 말이야?";
			link.l1.go = "Tuttuat_53";
		break;
		
		case "Tuttuat_53":
			dialog.text = "내가 도와주지, 백인. 네가 가져온 차빈 부적 두 개를 내가 줄게. 나는 조상 영혼들에게 말해 부적에 힘을 불어넣을 거야. 네가 그 중 하나를 가지고 있으면, 재규어 전사들과 평범한 병사처럼 싸울 수 있어. 그들처럼 될 수 있지만, 아주 강할 거야. 부적이 널 보호하고, 네 무기에 사원의 차비나비에게 상처를 입힐 힘을 줄 거다.";
			link.l1 = "부적들이 정말 도움이 될 거라고 확신하나?";
			link.l1.go = "Tuttuat_54";
		break;
		
		case "Tuttuat_54":
			dialog.text = "알고 있지. 나는 조상들과 대화한다. 나는 위대한 주술사다. 넌 나를 믿는다. 부적 두 개를 가져가라. 하나는 널 지켜주고, 다른 하나는 네 무기를 강하게 해준다. 반드시 부적 중 하나를 써야 한다. 어느 것을 쓸지는 네가 선택해라. 부적을 착용하지 않으면 재규어 전사들에게 죽게 될 것이다\n그리고 기억해라, 자정이 되면 윰 시밀이 네가 죽인 모든 전사들을 다시 살려낸다. 두 번 싸우지 않으려면 때를 잘 맞춰야 한다. 아니면 두 번 싸워도 된다; 영혼들이 내게 말하길, 네가 그렇게 할 수도 있다고 한다.";
			link.l1 = "알겠군.";
			link.l1.go = "Tuttuat_55";
		break;
		
		case "Tuttuat_55":
			dialog.text = "부적을 가져가라. 여기 있다. 하지만 기억해라, 이 부적의 힘에는 한계가 있다. 한 달이 지나면 그 힘은 약해진다. 내가 말했듯이, 너는 이 힘을 오래 가질 수 없다. 우리 부족의 위대한 주술사만이 이 힘을 다룰 수 있다.";
			link.l1 = "기억나. 그럼, 달이 하나뿐인 거야? 한 달만 있는 거야?";
			link.l1.go = "Tuttuat_56";
		break;
		
		case "Tuttuat_56":
			dialog.text = "그래. 유므 시밀의 신전에 가면, 제단을 찾아야 하고 그 안에 큰 콘도르 상이 있을 거야. 이곳이 신전에서 가장 중요한 부분이지. 여기서 유므 시밀의 옥 해골을 놓으면, 칼레우체에 걸린 저주가 풀릴 거다. 그가 다시 널 공격하더라도 평범한 인간처럼 쓰러뜨릴 수 있어. 그리고 나서 그가 네게서 빼앗아간 부적을 나에게 가져오면 된다.";
			link.l1 = "콘도르? 무슨 일이야?";
			link.l1.go = "Tuttuat_57";
		break;
		
		case "Tuttuat_57":
			dialog.text = "콘도르는 내 고향 산에 사는 위대한 새야. 고향을 그리워하며, 내 조상들이 신전 근처에 콘도르 상을 세웠지.";
			link.l1 = "좋아, 내가 찾아볼게...";
			link.l1.go = "Tuttuat_58";
		break;
		
		case "Tuttuat_58":
			dialog.text = "조심해라. 재규어 전사들 말고도 사원 안에는 많은 위험이 도사리고 있다.";
			link.l1 = "무슨 위험?";
			link.l1.go = "Tuttuat_59";
		break;
		
		case "Tuttuat_59":
			dialog.text = "확실히는 몰라. 직접 확인해 봐. 함정일 수도 있고, 그냥 혼란일 수도 있지. 신전에 들어가는 건 어렵다네. 입구가 봉인되어 있으니, 열 방법을 찾아야 해. 내 조상들은 위대한 전사이자 주술사였을 뿐만 아니라, 훌륭한 건축가이기도 했지. 그걸 열려면 머리를 써야 해.";
			link.l1 = "헤! 무섭게 들리지만, 다 덤벼도 상관없어! 나는 시간 낭비 안 해. 바로 출항한다!";
			link.l1.go = "Tuttuat_60";
		break;
		
		case "Tuttuat_60":
			dialog.text = "가거라, 백인 전사여. 내가 정령들을 불러 재규어 전사들과 칼레우체에 맞서 너를 도와주겠다. \n부적을 사용하면 내가 도와줄 수 있지만, 그렇지 않으면 네가 죽게 될 것이다.";
			link.l1 = "고맙습니다, 위대한 주술사님... 반드시 그렇게 하겠습니다.";
			link.l1.go = "Tuttuat_61";
		break;
		
		case "Tuttuat_61":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
			npchar.greeting = "Tuttuat_3";
			Log_Info("You have received two amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "kaleuche_amulet2");
			GiveItem2Character(pchar, "kaleuche_amulet3");
			// преобразуем амулеты
			ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_sword");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_shield");
			sld = ItemsFromID("kaleuche_amulet2");
			AddDescriptor(sld, M_AMULET_TYPE, AMULET_PAGAN);
			aref modifier = AddCallback(sld, CT_COMMON, "KaleucheAmuletAttack");
			modifier.arg0 = 0.25;
			sld.picIndex = 13;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			sld = ItemsFromID("kaleuche_amulet3");
			AddDescriptor(sld, M_AMULET_TYPE, AMULET_PAGAN);
			SetModifierFromSource(sld, HAS + M_CANT_BE_POISONED, true, TALISMAN_ITEM_TYPE);
			SetModifier(sld, M_REDUCE_DAMAGE, 0.25);
			sld.picIndex = 14;
			sld.picTexture = "ITEMS_36";
			sld.groupID = TALISMAN_ITEM_TYPE;
			sld.unique = true;	
			sld.ItemType = "ARTEFACT";
			SetFunctionTimerCondition("Caleuche_TuttuatAmuletOver", 0, 0, 30, false); // таймер
			// делаем доступным Хаэль Роа
			n = FindIsland("KhaelRoa");
			Islands[n].visible = true;
			Island_SetReloadEnableGlobal(Islands[n].id, true);
			Islands[n].reload.l1.radius = 150.0;
			Islands[n].reload.l2.label = "Shore64_1";
			Islands[n].reload.l2.name = "reload_2";
			Islands[n].reload.l2.go = "";
			Islands[n].reload.l2.emerge = "";
			Islands[n].reload.l2.radius = 0.0;
			Islands[n].reload.l2.pic = 0;
			Islands[n].reload.l2.tex = "t1";
			pchar.questTemp.Caleuche = "khaelroa";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1 = "location";
			pchar.quest.Caleuche_khaelroa_arrive.win_condition.l1.location = "KhaelRoa_port";
			pchar.quest.Caleuche_khaelroa_arrive.function = "Caleuche_KhaelRoaArrive";
			AddQuestRecord("Caleuche", "34");
			if (CheckAttribute(pchar, "questTemp.NatanStory")) 
			{
				pchar.questTemp.Caleuche.NatanInfo = "true";
				AddQuestUserData("Caleuche", "sText", "But I have a clue: it seems that white captain, who had visited the temple of the Chavins, is none other than my good friend Nathaniel Hawk. I remember him saying that he had a map of that island in Maroon Town. Guess I will pay Nathan a visit.");
			}
			else AddQuestUserData("Caleuche", "sText", "That's a huge area in the sea, but I have no choice. I'll have to scour it entirely. Shaman said North of Dominica, and not too far so I could steadily move North, it might very well be a bit to the East or West. He also mentioned some Captain that destroyed the undead ship maybe I will be lucky and I might find him one day, alas, he said that I have only one month to hold this power or whatever it is, oh well it is what it is, let the search begin!");
		break;
		
		case "Tuttuat_62":
			if (pchar.questTemp.Caleuche == "regard" && CheckCharacterItem(pchar, "kaleuche_amulet1") && CheckCharacterItem(pchar, "kaleuche_amulet2") && CheckCharacterItem(pchar, "kaleuche_amulet3")) 
			{
				dialog.text = "나는 영혼들과 대화하지. 너, 그 섬에 있었지, 윰 시밀의 신전에서. 칼레우체랑 부적을 찾았나?";
				link.l1 = "맞아요, 위대한 주술사님. 제가 섬을 찾아내고, 사원에 들어가서, 옥 해골을 안에 두고 나왔어요.";
				link.l1.go = "Tuttuat_63";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "가라, 하얀 전사야.";
				if (CheckAttribute(pchar, "questTemp.Caleuche.AmuletOver"))
				{
					link.l1 = "투투아타팍, 있잖아... 내가 해골을 제때 사원에 가져가지 못해서, 네 부적들이 힘을 잃었어.";
					link.l1.go = "Tuttuat_82";
				}
				else
				{
					link.l1 = "...";
					link.l1.go = "Tuttuat_62_1";
				}
			}
		break;
		
		case "Tuttuat_62_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_62";
		break;
		
		case "Tuttuat_63":
			npchar.greeting = "Tuttuat_2";
			pchar.quest.Caleuche_TuttuatAmuletOver.over = "yes"; //снять таймер
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet2")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			if(IsEquipCharacterByArtefact(pchar, "kaleuche_amulet3")) RemoveCharacterEquip(pchar, TALISMAN_ITEM_TYPE);
			dialog.text = "너는 칼레우체의 저주를 풀었지. 그 후에 그녀가 널 찾아왔나?";
			link.l1 = "그래. 우리는 바로 그 섬에서 만났지. 내가 그녀와 싸워서 이겼어. 이제 부적 세 개 모두 내 손에 있지. 자, 가져가.";
			link.l1.go = "Tuttuat_64";
		break;
		
		case "Tuttuat_64":
			RemoveItems(pchar, "kaleuche_amulet1", 1);
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			Log_Info("You have given three Chavin amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "너는 빠르고 강한 전사로구나, 창백한 얼굴을 가진 자여. 투투아타파크는 백인들을 좋아하지 않지만, 용감하고 능숙한 전사는 존중한다. 아주 잘했다. 너는 바다에서 칼레우체를 없앴다. 그리고 내게 부적 세 개를 가져왔지. 상을 주겠다.";
			link.l1 = "내가 영원히 가질 수 있는 '힘'에 대해 뭔가 약속했었지?";
			link.l1.go = "Tuttuat_65";
		break;
		
		case "Tuttuat_65":
			dialog.text = "네 말이 맞다. 그 힘을 주마. 카리브 해에서 내가 아는 그 식물의 비밀을 아는 자는 아무도 없다. 잘 들어라, 창백한 얼굴의 자여! 내 고향에는 약초가 있다. 우리는 그것을 망가 로사라 부른다. 그 식물에 대해 들어본 적 있느냐?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa.Tell"))
			{
				link.l1 = "그래. 내가 그걸 손에 들었었지. 집시들이 그 물건에 엄청난 관심을 보이더군. 그리고 그들 중 한 명인 치유사 아멜리아는 심지어...";
				link.l1.go = "Tuttuat_66";
			}
			else
			{
				link.l1 = "모르겠어...";
				link.l1.go = "Tuttuat_66_1";
			}
		break;
		
		case "Tuttuat_66":
			dialog.text = "나는 약초사 아멜리아에 대해 들었어. 그녀가 조금은 알지만, 많이 알지는 못하지. 망가 로사의 비밀은 알지 못해. 망가 로사가 이곳에 처음 전해졌던 내 고향에서 온 위대한 주술사만이 그 힘을 완전히 쓸 수 있지.";
			link.l1 = "무슨 힘?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_66_1":
			dialog.text = "이 약초는 내 고향에서 자라지만, 카리브 해에서도 볼 수 있지. 키가 크고 연둣빛인 식물로, 잎이 손가락을 펼친 야자수처럼 생겼고 향도 좋아. 보면 바로 알아볼 수 있어서 다른 것과 헷갈릴 일은 없어. 나는 이 식물의 비밀을 알고 있지. 여기서 힘을 뽑아낼 수 있어.";
			link.l1 = "알겠어, 그런데 어떤 힘 말이지?";
			link.l1.go = "Tuttuat_67";
		break;
		
		case "Tuttuat_67":
			dialog.text = "나는 망가 로사의 물약을 만들 수 있어. 아주 강한 물약이지. 카리브 해에서 나 말고는 이런 걸 만들 수 있는 사람이 없어. 내 물약을 마시면 영원히 더 강해지고, 더 빨라지고, 더 똑똑해지고, 눈도 더 날카로워지고, 더 잘생겨지고, 더 운도 좋아져. 너를 위해 그런 물약을 세 개 만들어주지.";
			link.l1 = "아주 흥미롭군!";
			link.l1.go = "Tuttuat_68";
		break;
		
		case "Tuttuat_68":
			dialog.text = "너는 훌륭한 전사니까, 먼저 네 몸을 더 튼튼하게 해주는 물약 하나와 더 빠르게 해주는 물약 하나가 필요해. 내가 그 두 가지를 만들고 나면, 세 번째 물약은 네가 직접 고르게 될 거야.\n하지만 그걸 만들려면 망가 로사가 필요해. 나는 지금 그게 하나도 없어.";
			link.l1 = "망가 로사를 어디서 찾아야 하지?";
			link.l1.go = "Tuttuat_69";
		break;
		
		case "Tuttuat_69":
			dialog.text = "망가 로사는 카리브 해에서 드문 약초다. 사람들이 잘 다니지 않는 곳에서 자라지. 멍청한 놈들이 그걸 따서 말리고 피우더군. 아주 멍청한 놈들이지. 절대 피우지 마라! 그 힘을 허비하는 짓이다... 정글이나 만, 멍청한 놈들이 얼씬도 못 하는 비밀스러운 곳을 찾아라. 잘 살펴봐라. 물약 하나를 만들려면 망가 로사 줄기 다섯 개가 필요하다.";
			link.l1 = "좋아, 위대한 주술사. 내가 망가 로사를 충분히 모으면 다시 오겠소.";
			link.l1.go = "Tuttuat_70";
		break;
		
		case "Tuttuat_70":
			dialog.text = "가거라, 하얀 전사여. 망가 로사를 가져오너라. 후회하지 않을 것이다. 내 물약이 최고다. 내가 영혼들에게 네 수색을 도와달라고 말해주마.";
			link.l1 = "고마워! 또 보자, 주술사!";
			link.l1.go = "Tuttuat_71";
		break;
		
		case "Tuttuat_71":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			pchar.questTemp.Caleuche = "mangarosa";
			pchar.questTemp.Caleuche.Mangarosa = 0;
			AddQuestRecord("Caleuche", "41");
		break;
		
		case "Tuttuat_72":
			dialog.text = "물약을 위해 망가 로사 다섯 줄기 가져왔나?";
			if (GetCharacterItem(pchar, "cannabis7") >= 5)
			{
				link.l1 = "그래. 네가 필요한 식물 다섯 가지 여기 있다.";
				link.l1.go = "Tuttuat_73";
			}
			link.l2 = "아직 아닙니다, 위대한 주술사님. 제 탐색은 계속되고 있습니다...";
			link.l2.go = "Tuttuat_72_1";
		break;
		
		case "Tuttuat_72_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
		break;
		
		case "Tuttuat_73":
			RemoveItems(pchar, "cannabis7", 5);
			switch (sti(pchar.questTemp.Caleuche.Mangarosa))
			{
				case 0:
					dialog.text = "아주 좋아. 내일 해가 지면 오게나. 자네의 반사 신경과 민첩성을 높여줄 물약을 만들어 주지.";
					link.l1 = "좋아, 주술사. 내일 저녁에 올게.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 1;
				break;
				
				case 1:
					dialog.text = "아주 좋아. 내일 해가 지면 오시오. 그대의 체력을 높여줄 물약을 만들어 주겠소.";
					link.l1 = "알겠소, 주술사. 내일 저녁에 오겠소.";
					link.l1.go = "Tuttuat_74";
					pchar.questTemp.Caleuche.Mangarosa = 2;
				break;
				
				case 2:
					dialog.text = "아주 좋아. 어느 물약을 고르겠나? 힘의 물약, 예리한 시야의 물약, 지능의 물약, 아름다움의 물약, 아니면 행운의 물약인가?";
					link.l1 = "힘의 물약.";
					link.l1.go = "Tuttuat_77_1";
					link.l2 = "예리한 시야의 물약.";
					link.l2.go = "Tuttuat_77_2";
					link.l3 = "지능의 물약.";
					link.l3.go = "Tuttuat_77_3";
					link.l4 = "미모의 물약.";
					link.l4.go = "Tuttuat_77_4";
					link.l5 = "행운의 물약.";
					link.l5.go = "Tuttuat_77_5";
				break;
			}
		break;
		
		case "Tuttuat_74":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1 = "Timer";
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.hour  = 19.0;
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Caleuche_mangarosa_potion.function = "Caleuche_MangarosaPotion";
		break;
		
		case "Tuttuat_75":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Potion"))
			{
				sTemp = "";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1) sTemp = "  It make your movements faster, and you better fight with fine light weapons.";
				if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2) sTemp = "  It make you more hardy in long journeys, and you better fight with sharp sabers.";
				dialog.text = "물약 다 됐어, 창백한 전사야. 가져가."+sTemp+"";
				link.l1 = "고맙소, 위대한 주술사님.";
				link.l1.go = "Tuttuat_76";
			}
			else
			{
				dialog.text = "아직 준비 안 됐어, 백인놈. 나중에 다시 와. 방해하지 마.";
				link.l1 = "좋아...";
				link.l1.go = "Tuttuat_75_1";
			}
		break;
		
		case "Tuttuat_75_1":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_75";
		break;
		
		case "Tuttuat_76":
			if (sti(pchar.questTemp.Caleuche.Mangarosa) > 2)
			{
				dialog.text = "약속한 물약은 전부 만들어 놨어. 이제 더 강해질 거야. 기분 좋지?";
				link.l1 = "그래, 위대한 주술사여. 정말로 값진 보상이었소.";
				link.l1.go = "Tuttuat_78";
			}
			else
			{
				dialog.text = "Manga Rosa 줄기 다섯 개를 더 찾아서 나에게 가져와. 내가 또 다른 물약을 만들어 줄게.";
				link.l1 = "더 가져다줄게. 또 보자!";
				link.l1.go = "Tuttuat_77";
			}
		break;
		
		case "Tuttuat_77":
			DialogExit();
			npchar.dialog.currentnode = "Tuttuat_72";
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 1)
			{
				ChangeItemDescribe("kaleuche_amulet1", "itmdescr_kaleuche_amulet1_potion");
				sld = ItemsFromID("kaleuche_amulet1");
				sld.name = "itmname_kaleuche_amulet1_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet1");
			}
			if (sti(pchar.questTemp.Caleuche.Mangarosa) == 2)
			{
				ChangeItemDescribe("kaleuche_amulet2", "itmdescr_kaleuche_amulet2_potion");
				sld = ItemsFromID("kaleuche_amulet2");
				sld.name = "itmname_kaleuche_amulet2_potion";
				sld.groupID = SPECIAL_ITEM_TYPE;
				sld.picIndex = 15;
				sld.picTexture = "ITEMS_35";
				sld.price = 0;
				sld.Weight = 1.0;
				sld.ItemType = "SUPPORT";
				GiveItem2Character(pchar, "kaleuche_amulet2");
			}
		break;
		
		case "Tuttuat_77_1":
			dialog.text = "내일도 평소처럼 와. 내가 네 힘을 키워줄 물약을 만들어 줄 테니, 큰 도끼로 더 잘 싸울 수 있을 거야.";
			link.l1 = "좋아.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 31;
		break;
		
		case "Tuttuat_77_2":
			dialog.text = "내일도 평소처럼 오게. 네 눈을 날카롭게 해줄 물약을 만들어 줄 테니, 모든 표적이 잘 보일 거고, 불을 뿜는 무기로 더 잘 때릴 수 있을 거야.";
			link.l1 = "좋아.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 32;
		break;
		
		case "Tuttuat_77_3":
			dialog.text = "내일도 평소처럼 오게. 내가 머리 좋아지는 약을 지어줄 테니, 적들한테는 잘 숨는 게 좋을 거야.";
			link.l1 = "좋아.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 33;
		break;
		
		case "Tuttuat_77_4":
			dialog.text = "내일도 평소처럼 오게나. 내가 자네를 더 잘생기게 해 주는 물약을 만들어 줄 테니, 사람들을 설득하는 데도 더 능해질 걸세.";
			link.l1 = "좋아.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 34;
		break;
		
		case "Tuttuat_77_5":
			dialog.text = "내일도 평소처럼 오게. 내가 네 운이 더 좋아지도록 약을 지어줄 테니, 행운이 따를 거야.";
			link.l1 = "좋아.";
			link.l1.go = "Tuttuat_74";
			pchar.questTemp.Caleuche.Mangarosa = 35;
		break;
		
		case "Tuttuat_78":
			dialog.text = "내 예술, 위대한 주술사의 예술을 마음에 들어해 줘서 기쁘다.";
			link.l1 = "있지, Tuttuathapak, 이 세 개의 부적이 왜 필요했던 거야? 그냥 궁금해서 물어보는 거야...";
			link.l1.go = "Tuttuat_79";
		break;
		
		case "Tuttuat_79":
			dialog.text = "이 두 부적의 힘이 이미 느껴지지? 정령들이 나를 도와 이 부적들을 더 강하게 만들어 줄 거야. 그리고 세 개의 부적이 모두 모이면, 내 조상들, 위대한 차빈족의 위대한 주술적 지혜와 깨달음을 얻게 될 거다.";
			link.l1 = "알겠소. 좋아, 훌륭한 물약을 다시 한 번 고맙소. 그대는 정말 대단한 주술사요. 이제 나는 가야겠소. 잘 있소, 투투아타파크. 다시 만날 수 있기를 바라오.";
			link.l1.go = "Tuttuat_80";
		break;
		
		case "Tuttuat_80":
			dialog.text = "안녕히 가시오, 하얀 전사여. 이제 더 이상 나를 찾을 필요 없소. 나는 은둔하여 조상들의 지혜를 깨우치려 하오. 당신의 여정에 영혼들이 함께하길 바라오!";
			link.l1 = "그렇다면... 하... 위대한 주술사여, 정령들이 그대의 길도 인도하길. 잘 가시오...";
			link.l1.go = "Tuttuat_81";
		break;
		
		case "Tuttuat_81":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			GiveItem2Character(pchar, "kaleuche_amulet3");
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet3_potion");
			sld = ItemsFromID("kaleuche_amulet3");
			sld.name = "itmname_kaleuche_amulet3_potion";
			sld.groupID = SPECIAL_ITEM_TYPE;
			sld.picIndex = 15;
			sld.picTexture = "ITEMS_35";
			sld.price = 0;
			sld.Weight = 1.0;
			sld.reaction = sti(pchar.questTemp.Caleuche.Mangarosa);
			sld.ItemType = "SUPPORT";
			i = sti(sld.reaction);
			ChangeItemDescribe("kaleuche_amulet3", "itmdescr_kaleuche_amulet"+i+"_potion");
			AddQuestRecord("Caleuche", "42");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			DeleteAttribute(pchar, "questTemp.Caleuche.Mangarosa");
			DeleteAttribute(pchar, "questTemp.Caleuche.Potion");
		break;
		
		case "Tuttuat_82":
			Log_Info("You have given amulets");
			RemoveItems(pchar, "kaleuche_amulet2", 1);
			RemoveItems(pchar, "kaleuche_amulet3", 1);
			dialog.text = "너 때문에 슬프구나, 창백한 얼굴이여. 내가 영혼들과 의식을 치러 이 부적에 힘을 불어넣었는데, 네가 그걸 허비했어. 나는 슬프다. 이제 가라. 투투아타팍은 더 이상 너에게 할 말이 없다.";
			link.l1 = "미안해, 그냥 정말 운이 없었어... 뭐, 어쩔 수 없지. 잘 가, 주술사.";
			link.l1.go = "Tuttuat_83";
		break;
		
		case "Tuttuat_83":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Caleuche", "43");
			pchar.questTemp.Caleuche = "end";
			CloseQuestHeader("Caleuche");
			sld = ItemsFromID("SkullAztec");
			sld.price = 10000;
		break;

		// капитан Калеуче
		case "CaleucheCap":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_01.wav");
			dialog.text = "다 소용없다, 선원. 너는 나를 이길 수 없어. 그리고 갑판에 쓰러진 내 부하들도 새벽이 오기 전에 뼈를 모아 다시 일어날 거다. 우리는 죽일 수 없어, 죽음이 우리를 영원히 버렸으니까.";
			link.l1 = "젠장! 살아 있는 거냐, 죽은 거냐? 아무래도 살아 있는 것 같군 – 죽은 자들은 보통 조용히 누워 있고 칼을 휘두르진 않지. 그런데 넌 누구고, 왜 내 배를 공격한 거야?";
			link.l1.go = "CaleucheCap_1";
		break;
		
		case "CaleucheCap_1":
			dialog.text = "나는 플라잉 하트의 발타자르 드 코르데스다. 나에 대해 아무것도 모르는 한심한 겁쟁이들은 나를 플라잉 더치맨의 선장 반 데르 데켄이라 부르지. 하지만 그건 중요하지 않다. 중요한 건 네가 지금 부적을 가지고 있다는 거고, 내가 그걸 가져가겠다는 거다. 그게 필요하다! 느껴진다! 차빈족의 위대한 부적, 셋 중 하나가 마침내 내 것이 될 것이다! 내 앞에 무릎 꿇어라, 필멸자여! 그러면 네 죽음을 고통 없이 끝내줄 수도 있지!";
			link.l1 = "지옥에나 떨어져라, 시체야!";
			link.l1.go = "CaleucheCap_2";
		break;
		
		case "CaleucheCap_2":
			DialogExit();
			npchar.MultiFighter = 4.0;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetCheckMinHP(pchar, 10, true, "Caleuche_GhostshipGetOut");
		break;
		
		case "CaleucheCap_3":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_02.wav");
			dialog.text = "믿을 수가 없어! 마지막으로 내 피를 본 게 언제였는지, 고통을 느낀 게 언제였는지 정말 오래됐는데... 어떻게 된 거지?!";
			link.l1 = "이번에는 네가 졌다, Balthazar de Cordes. 나는 네 이야기를 알고 있다. 비취 해골은 차빈 신전으로 돌아갔고, Yum Cimil의 저주는 이제 너와 네 선원들에게 더 이상 드리워지지 않는다. 이제는 네 선원들을 다시 살려낼 수 없을 것이다.";
			link.l1.go = "CaleucheCap_4";
		break;
		
		case "CaleucheCap_4":
			dialog.text = "오, 그래서 자네는 자신이 구원자라고 생각하나? 천만에! 발타자르 데 코르데스는 남은 목숨을 결코 헛되이 넘기지 않을 거다!";
			link.l1 = "플라잉 하트의 마지막 항해는 여기, 카엘 로아에서 끝난다. 그리고 너는 스물다섯 해 전처럼 네 배를 바닷속에서 다시 일으키지 못할 거다.";
			link.l1.go = "CaleucheCap_5";
		break;
		
		case "CaleucheCap_5":
			PlaySound("Voice\English\LE\Baltazar_de_Kortes\Baltazar_03.wav");
			dialog.text = "호크! 스물다섯 해가 흘렀지만, 아직도 어제 일처럼 기억나. 우리를 눈멀게 하고 내 배를 반으로 쪼갠 그 구슬의 광채. 그게 플라잉 하트와 발타자르 드 코르데스의 첫 패배이자 마지막 패배였지... 그러니 마지막으로 한 번 더 칼을 맞대자, 선장! 전장에서의 죽음이란 가볍고도 반가운 법이야!";
			link.l1 = "...";
			link.l1.go = "CaleucheCap_6";
		break;
		
		case "CaleucheCap_6":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Caleuche_ChangeShip");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Caleuche_Alonso_1":
			dialog.text = "더러운 건 다 치웠습니다, 선장. 이번엔 죽은 자들이 다시 안 일어났어요. 그런데 이 배 자체는... 어떻게 아직도 떠 있는지 모르겠습니다, 젠장.";
			link.l1 = "저주가 그녀를 붙잡고 있었어, Alonso. 하지만 이제 그건 끝났어.";
			link.l1.go = "Caleuche_Alonso_2";
		break;
		
		case "Caleuche_Alonso_2":
			dialog.text = "명령이 무엇입니까? 불을 질러버릴까요 – 그리고 끝내버릴까요?";
			link.l1 = "생각해 보겠소. '플라잉 하트'는 거의 박살나기 직전이었는데도 우리 배를 벌집으로 만들 뻔했지.";
			link.l1.go = "Caleuche_Alonso_3";
		break;

		case "Caleuche_Alonso_3":
			dialog.text = "화력만큼은 이 난파선이 정말 끝내주지, 세 번이나 저주할 놈이지만... 내가 하려던 말은 이거야 - 우리 선원 중에 자크라는 녀석이 있어...";
			link.l1 = "자크 트뤼도? 기억나. 최근에 우리랑 합류했지, 맞지?";
			link.l1.go = "Caleuche_Alonso_4";
		break;

		case "Caleuche_Alonso_4":
			dialog.text = "아이, 선장. 그게 말이죠, 그 악당은 값나가는 물건을 기가 막히게 잘 맡아내는 놈입니다 - 정말 대단해요. 언데드들이 조용해지자마자 녀석이 침대 중 하나로 달려가더니, 그 밑으로 기어들어가서 상자를 꺼냈습니다. 그리고 그 상자 안에는... 오천 두블론이나 있었어요!";
			link.l1 = "오천이라고? 흠... 발타자르 드 코르데스와 그 일당이 저주에서 벗어나려고 정말 애썼던 모양이군. 주머니에 금을 가득 채우고, 모든 게 끝나면 편하게 살 꿈을 꾸었겠지...";
			link.l1.go = "Caleuche_Alonso_5";
		break;
		
		case "Caleuche_Alonso_5":
			dialog.text = "우리 선원들도 그렇게 살면 싫지 않을 거야, 선장... 놈들에게 나눠주면 평생 잊지 않을 거고, 안 나눠주면 그건 또 평생 기억할 거야.";
			link.l1 = "알론소, 네 말이 맞아. 선원들에게 조금은 즐기게 해줘야지 - 그럴 자격이 있지. 그들에게 절반을 나눠주고, 자크는 일주일 동안 당직에서 쉬게 해. 오늘은 그록 대신 럼주를 마시게 허락하마. 하지만 방심하지 마라 - 바다는 실수를 용서하지 않는다는 걸 알잖아.";
			link.l1.go = "Caleuche_Alonso_6";
			link.l2 = "흠... 알론소, 네 말이 맞을지도 모르겠군. 선원들도 좀 풀어질 필요가 있지. 몫의 4분의 1을 나눠줘라. 그리고 저 술고래들이 우리가 어느 항구에 닻을 내리기 전에는 잔치를 시작하지 못하게 잘 지켜봐라.";
			link.l2.go = "Caleuche_Alonso_7";
			link.l3 = "그래서 그 게으름뱅이들이 첫 항구에서 선술집이랑 창관으로 흩어지라고? 내가 한 달 내내 하나씩 데려올 생각은 없어. 내가 주는 임금이면 충분해. 그리고 두블룬은 여기로 가져와. 아무도 슬쩍할 생각 못 하게.";
			link.l3.go = "Caleuche_Alonso_8";
		break;
		
		case "Caleuche_Alonso_6":
			dialog.text = "알겠습니다, 선장님. 그리고 걱정 마십시오, 녀석들이 절대 선장님을 실망시키지 않을 겁니다.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_2");
		break;
		
		case "Caleuche_Alonso_7":
			dialog.text = "그래, 선장. 그 악마놈들 다루는 법은 내가 잘 알지 – 나만 믿으시오.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_3");
		break;
		
		case "Caleuche_Alonso_8":
			dialog.text = "명령대로 하겠습니다, 선장님. 선원들은 물론 더 바라긴 했지만... 여기서는 선장님이 결정하셔야죠.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_AlonsoAfterWinOnShip_4");
		break;
		
		// --> // наш матрос на берегу
		case "on_coast":
			dialog.text = "드디어 깨어났군, 선장... 기분이 어떤가?";
			link.l1 = "젠장, 무슨 일이야? 머리가 아파서 쪼개질 것 같아...";
			link.l1.go = "on_coast_1";
		break;
		
		case "on_coast_1":
			dialog.text = "우리가 선장 선실에 들어갔을 때, 너는 바닥에 누워 있었고, 여전히 꼼짝도 하지 않았지. 선원들이 너를 들어 올려 우리 배로 끌고 갔어 – 정말 아슬아슬했지, 갑판에 쓰러져 있던 시체들이 다시 일어나기 시작했으니까\n지극히 거룩하신 성모님과 모든 성인들이시여! 우리는 급히 밧줄을 끊고 도망치려 했지만, 그들의 배에서 날아온 일제 사격에 우리 낡은 배는 산산조각이 나 버렸고, 배를 통제할 수 없게 되었어. 그리고 그들은 돛을 올리더니 눈 깜짝할 사이에 사라져 버렸지\n우리 배는 좌초했고, 살아남은 자들은 보트를 타고 겨우 해안에 도착했어. 오늘 많은 훌륭한 사람들이 죽었지... 우리가 그냥 배에 남아 있었더라면... 하지만 우리는 폭풍이 배를 완전히 끝장낼 거라고 확신했었어.";
			link.l1 = "자네들 잘못이 아니야, 신사분들. 올바른 판단이었어. 고맙네, 기억하겠네.";
			link.l1.go = "on_coast_2";
		break;
		
		case "on_coast_2":
			dialog.text = "우리가 너를 배로 끌어올린 다음, 육지로 데려왔어. 거의 죽을 뻔했지...";
			link.l1 = "내가 목숨을 빚졌군. 내가 여기서 얼마나 오래 의식을 잃고 누워 있었지?";
			link.l1.go = "on_coast_3";
		break;
		
		case "on_coast_3":
			dialog.text = "하루 종일이었어. 네 상처를 씻고 붕대를 감아줬지, 약도 먹이고 럼주도 좀 부어 넣었어. 곧 괜찮아질 거야.";
			link.l1 = "이번에는 정말 죽지 않을 거야. 그래도 몸이 별로 안 좋긴 하지만...";
			link.l1.go = "on_coast_4";
		break;
		
		case "on_coast_4":
			dialog.text = "그건 확실하지... 플라잉 더치맨이었나, 선장? 왜 우리를 공격한 거지? 그리고 왜 승선하기 전엔 사격하지 않다가, 한 번에 포격해서 우리 배를 거의 침몰시킨 거야?";
			link.l1 = "그들의 선장은 내가 인디언 주술사 투투아타파크에게 말했던 그 부적이 필요했어. 그래서 우리를 바로 침몰시키지 않았던 거지. 하지만 그들의 두목이 부적을 손에 넣자마자, 곧바로 우리를 처리해 버렸어... 이게 무슨 악몽이람! 죽은 자들이 조종하는 배라니! 도저히 믿을 수가 없어...\n";
			link.l1.go = "on_coast_5";
		break;
		
		case "on_coast_5":
			dialog.text = "그래, 이제 우리가 플라잉 더치맨을 만날 차례였지. 기회가 되면 교회에 가서, 기적적으로 살아난 걸 감사하며 촛불을 켜고 주님께 기도드릴 거야...";
			link.l1 = "나도 그래... 아마도. 하지만 먼저 그 마을로 돌아갈 거야. 투투아타파크에게 이 모든 걸 다 말해야 해. 저 저주받은 배가 우리를 공격한 건 바로 그 부적 때문이었어! 분명 그 붉은 피부의 악마는 왜 그 산 자의 시체들이 그걸 필요로 했는지 어느 정도 알고 있었을 거야.";
			link.l1.go = "on_coast_6";
		break;
		
		case "on_coast_6":
			dialog.text = "알겠어. 하지만 조심해, 선장. 네 상처가 아직 다 낫지 않았잖아. 최소한 혹시 모르니 누군가 데리고 가.";
			link.l1 = "조심할게, 약속해. 버리지 않아줘서 고마워!";
			link.l1.go = "on_coast_7";
		break;
		
		case "on_coast_7":
			dialog.text = "무슨 소리야, 선장! 우린 선장님을 위해서라면 땅끝까지라도 따라가고, 수천 마리 언데드와도 싸울 거야! 이렇게 많이 잃은 건 정말 아깝지만, 이 이야기는 전설로 남을 거야.";
			link.l1 = "...";
			link.l1.go = "on_coast_8";
		break;
		
		case "on_coast_8":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("Caleuche", "5");
		break;
		
		// Фергус Хупер
		case "fergus":
			dialog.text = "이봐! 아직 너한테 팔 만큼 뱀 가죽을 충분히 모으지 못했으니까, 꺼져!";
			link.l1 = "흠... 너 퍼거스 후퍼냐?";
			link.l1.go = "fergus_1";
			DelLandQuestMark(npchar);
		break;
		
		case "fergus_1":
			dialog.text = "아니, 내 이름은 투투아타팍이다. 당장 꺼지지 않으면 저주를 내릴 거다. 그러니 어서 사라지는 게 좋을 거다, 안 그러면...";
			link.l1 = "...미쳐버리고, 내 배에 불을 지르고, 내 선원들이 날 죽이고 내 모든 걸 가져가겠지. 맞지?";
			link.l1.go = "fergus_2";
		break;
		
		case "fergus_2":
			sld = characterFromId(pchar.questTemp.Caleuche.Amuletmaster);
			dialog.text = "아르... 뭐야, 넌 누구야!? 어떻게...";
			link.l1 = "우리에게 공통된 친구가 있어. 퍼거스라는 놈이지. 등대지기인데, 이름은 "+GetFullName(sld)+". 그가 당신에 대해 말해줬고, 나를 당신에게 보내 찾으라고 했어. 그런데 말이지, 나 투투아타파크 샤먼을 개인적으로 알아. 그러니까 네 농담은 안 통했어, 미안하다. 들어봐, 난 문제 일으키러 온 게 아니야. 너한테서 뭔가 사고 싶은 게 있어. 그리고 그건 뱀가죽이 아니야.";
			link.l1.go = "fergus_3";
		break;
		
		case "fergus_3":
			dialog.text = "오, 내 오랜 친구를 아는구나! 그 친구는 잘 지내나? 등대에서 지루함에 죽지는 않았겠지? 자, 앉아, 선원. 나랑 한잔 하자!";
			link.l1 = "미안하네, Fergus. 지금 정말 시간이 없어. 들어봐, 나는 그 인디언 부적이 필요해. 네가 말한, 네 전 선장이 Tuttuathapak과 함께 본토에서 가져온 것 중 하나 말이야. 내가 좋은 값에 사겠네, 그러면 자네도 위험한 물건에서 벗어날 수 있을 거야.";
			link.l1.go = "fergus_4";
		break;
		
		case "fergus_4":
			dialog.text = "그게 뭐가 그렇게 위험하다는 거지? 지금까지 아무 해도 본 적 없어. 그냥 쓸모없는 돌일 뿐이야";
			link.l1 = "그건 네가 더 이상 바다를 누비지 않기 때문이지. 나도 얼마 전까지 비슷한 부적을 가지고 있었어. 유령선이 이런 것들을 쫓고 있거든.";
			link.l1.go = "fergus_5";
		break;
		
		case "fergus_5":
			dialog.text = "장난하냐, 친구? 혹시 투투아타파크를 알게 된 게 너한테 악영향을 준 거 아니야? 조심해, 선장. 그 붉은 피부의 악마가 네 정신을 잡아먹을 거야...";
			link.l1 = "믿거나 말거나, 나는 진실을 말하고 있어. 내가 직접 두 눈으로 보지 않았다면 나도 안 믿었을 거야. 성경에라도 맹세할 수 있고, 나랑 같이 있었던 사람들에게 물어봐도 돼. 그 칼레우체와 마주친 뒤에 겨우 살아남았으니까.";
			link.l1.go = "fergus_6";
		break;
		
		case "fergus_6":
			dialog.text = "칼레우체?";
			link.l1 = "음, 대부분은 그걸 플라잉 더치맨이라고 부르지만, 진짜 이름은 플라잉 하트야. 뭐, 상관없지. 그냥 그 부적을 나한테 팔아. 어차피 너한테는 쓸모없는 거잖아, 나도 알아.";
			link.l1.go = "fergus_7";
		break;
		
		case "fergus_7":
			dialog.text = "맞아. 이건 그냥 쓸모없는 장신구일 뿐이야, 꽤 예쁘긴 하지만. 들어봐, 내가 별다른 조건 없이 너한테 팔았을 텐데, 이제는 그걸 가지고 있지 않아. 내가 정글에서 사냥하는 동안 오두막에서 다른 물건들과 함께 도둑맞았거든. 그게 얼마 전, 한 달쯤 전에 일어난 일이야. 미안하지만, 내가 도와줄 수 있는 건 없어.";
			link.l1 = "그리고 누가 그걸 훔쳤지?";
			link.l1.go = "fergus_8";
		break;
		
		case "fergus_8":
			dialog.text = "내 집을 털어간 놈들이 누군지 알았다면 내가 여기 앉아 있겠어? 벨리즈 밖에서 도둑놈들과 강도 떼가 돌아다니고 있는데, 그놈들 정보원들이 마을 안에도 있어. 뭐, 적어도 사령관은 그렇게 생각하지. 난 분명히 그놈들 짓이라고 확신해.";
			link.l1 = "사령관이 그 산적들에 대해 알고도 아직도 아무것도 안 해?";
			link.l1.go = "fergus_9";
		break;
		
		case "fergus_9":
			dialog.text = "그가 뭔가를 하고 있는지 아닌지는 나도 몰라. 내가 확실히 아는 건 내 소지품이 사라졌고, 네 소중한 부적도 함께 없어졌다는 거야. 저 도적들을 찾아봐. 어쩌면 그놈들 주머니에서 찾을 수 있을지도 몰라. 그걸 팔았을 가능성은 적어. 상인들은 그런 물건에 관심이 없으니까.";
			link.l1 = "좋아, 내가 사령관을 만나러 갈게. 행운을 빌어, 퍼거스!";
			link.l1.go = "fergus_10";
		break;
		
		case "fergus_10":
			DialogExit();
			AddQuestRecord("Caleuche", "9");
			pchar.questTemp.Caleuche.Bandos = "start"; 
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// бандит в городе
		case "Beliz_townbandos":
			dialog.text = "이봐! 뭐야, 뭘 원해? 손님 따윈 올 줄 몰랐거든. 꺼져!";
			link.l1 = "왜 그렇게 무례하게 구는 거야, 친구? 그냥 물어보고 싶었을 뿐이야...";
			link.l1.go = "Beliz_townbandos_1";
		break;
		
		case "Beliz_townbandos_1":
			dialog.text = "못 들었어? 당장 꺼져, 아니면 내가 직접 내쫓아줄 테니까!";
			link.l1 = "흠... 그래, 어쩌면 내가 찾던 사람이 너일지도 모르겠군. 그런데 너무 긴장한 것 같은데, 이봐...";
			link.l1.go = "Beliz_townbandos_2";
		break;
		
		case "Beliz_townbandos_2":
			dialog.text = "네가 아주 똑똑하다고 생각하지? 다시 말하지만, 지금 당장 꺼지든가, 아니면 경비들을 불러서 너를 감옥에 쳐넣게 할 거야!";
			link.l1 = "나를 감옥에 집어넣겠다고? 정말 흥미로운데. 이제야 내가 찾던 사람을 거의 확실히 찾았다는 생각이 드는군. 좋아, 동의하지. 경비병을 부르자고, 그리고 우리 모두 행복한 가족처럼 함께 사령관 사무실로 걸어가자고. 방금 거기 다녀왔으니 길도 기억나... 경비병! 경비병들!";
			link.l1.go = "Beliz_townbandos_3";
		break;
		
		case "Beliz_townbandos_3":
			dialog.text = "꺼져라! 네놈을 베어버리겠다!";
			link.l1 = "오호호! 그래, 한번 해보시지!";
			link.l1.go = "Beliz_townbandos_4";
		break;
		
		case "Beliz_townbandos_4":
			DialogExit();
			DeleteAttribute(npchar, "CityType");
			DeleteAttribute(npchar, "city"); // чтобы не было НЗГ
			LAi_SetImmortal(npchar, false);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_BelizTownbandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.Caleuche_letter.win_condition.l1 = "item";
			pchar.quest.Caleuche_letter.win_condition.l1.item = "kaleuche_letter";
			pchar.quest.Caleuche_letter.function = "Caleuche_FindLetter";
		break;
		
		// главарь лесных бандосов
		case "Beliz_forestbandos":
			dialog.text = "이봐, 여행자! 어서 와, 어서 와... 저녁도 있고, 잠자리도 있고, 돈만 내면 뭐든 다 있지. 그러니 주머니 다 털릴 준비나 해!";
			link.l1 = "그렇게 서두르지 마시오, 이봐. 너와 볼 일이 있거든.";
			link.l1.go = "Beliz_forestbandos_1";
		break;
		
		case "Beliz_forestbandos_1":
			dialog.text = "장사? 하하! 네가 할 일은 가진 은과 금을 전부 내놓는 것뿐이야!";
			link.l1 = "닥쳐라. 네가 기다리던 벨리즈에서 온 편지를 내가 가져왔다. 전령이 경비병들을 통과하지 못해서 나에게 이 일을 맡겼다.";
			link.l1.go = "Beliz_forestbandos_2";
		break;
		
		case "Beliz_forestbandos_2":
			dialog.text = "보여 줘!";
			link.l1 = "여기...";
			link.l1.go = "Beliz_forestbandos_3";
		break;
		
		case "Beliz_forestbandos_3":
			Log_Info("You have given a note");
			PlaySound("interface\important_item.wav");
			RemoveItems(pchar, "kaleuche_letter", 1);
			dialog.text = "(읽으면서) 흠... 그거 참 이상하군... 어떻게 휘말리게 된 거지?";
			link.l1 = "이미 말했잖아, 네 놈을 잡아갔길래 내가 그 일 맡았지. 그는 돈이랑 네가 따뜻하게 맞아줄 거라고 약속했어...";
			link.l1.go = "Beliz_forestbandos_4";
		break;
		
		case "Beliz_forestbandos_4":
			dialog.text = "따뜻하게 환영해달라고? 좋아, 이 친구야. 우리가 몸도 녹여주고, 밥도 먹이고, 돈도 좀 쥐여주고, 뭐든 해주지. 하지만 너도 우리한테 네가 경비대의 개가 아니라는 걸 증명해야 해. 지금 우리도 해결해야 할 일이 있거든.\n근처 만에 상인이 하나 막 도착했어. 들리는 말로는, 세관을 피해 물건을 도시로 들여오려는 모양이더라. 하지만 우리는 그놈한테서도 세금을 받아낼 거야. 우리도 법 지키는 사람들이니까! 같이 가자. 칼날이 어느 쪽인지 정도는 알지?";
			link.l1 = "나도 이 일의 몫을 받을 수 있나?";
			link.l1.go = "Beliz_forestbandos_5";
		break;
		
		case "Beliz_forestbandos_5":
			dialog.text = "틀림없이 그렇게 될 거야! 싸움에서 용감하고 살아남는다면 말이지. 하지만 쉽게 끝날 거라 기대하지 마, 상인은 혼자가 아니고, 호위가 있어. 그것도 아주 많은 호위지. 자, 이제 갈 시간이야 - 먹잇감이 가까워. 얘들아! 무기 준비해라, 나간다!\n";
			link.l1 = "...";
			link.l1.go = "Beliz_forestbandos_6";
		break;
		
		case "Beliz_forestbandos_6":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.GenQuest.CannotWait = true;//запрет ожидания
			LocatorReloadEnterDisable(pchar.location, "reload2_back", true);
			LocatorReloadEnterDisable(pchar.location, "reload3_back", true);
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("Beliz_forestbandos_"+i);	
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TMP_FRIEND");
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Beliz_ExitTown", "goto", "goto"+(rand(1)+1), "", 10.0);
			}
			DoQuestCheckDelay("OpenTheDoors", 12.0);
			pchar.quest.Caleuche_bandosrobb.win_condition.l1 = "location";
			pchar.quest.Caleuche_bandosrobb.win_condition.l1.location = "Beliz_ExitTown";
			pchar.quest.Caleuche_bandosrobb.function = "Caleuche_JungleBandosRobbery";
		break;
		
		case "Beliz_forestbandos_7":
			dialog.text = "겁쟁이가 아니구나. 잘했어! 네 몫을 받을 자격이 있지. 어떻게 받고 싶어? 현금으로? 아니면 물건으로? 술도 많이 실려 있었으니, 좋은 값에 팔릴 거야.";
			link.l1 = "현금.";
			link.l1.go = "Beliz_forestbandos_8_1";
			link.l2 = "상품이다.";
			link.l2.go = "Beliz_forestbandos_8_2";
		break;
		
		case "Beliz_forestbandos_8_1":
			Log_Info("You have received 100 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 100);
			dialog.text = "자, 여기 있다! 그리고 이 돈주머니는 편지를 전달해 준 대가야.";
			link.l1 = "고마워! 바로 이게 내가 원하는 거야!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_8_2":
			Log_Info("You have received 30 bottles of rum");
			Log_Info("You have received 12 bottles of wine");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "potionrum", 30);
			TakeNItems(pchar, "potionwine", 12);
			dialog.text = "자, 여기 있다! 죽도록 마시지만 말라고, 하하하! 그리고 이 돈주머니는 편지를 전해 준 대가다.";
			link.l1 = "고마워! 바로 이렇게 해야 내 마음에 들어!";
			link.l1.go = "Beliz_forestbandos_9";
		break;
		
		case "Beliz_forestbandos_9":
			Log_Info("You have received a purse");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "purse2", 1);
			dialog.text = "내 눈엔 자네가 괜찮은 놈으로 보이는데. 일 하나 더 해볼래? 자네가 내게 전해준 그 편지에 관한 일이야.";
			link.l1 = "그래.";
			link.l1.go = "Beliz_forestbandos_10";
		break;
		
		case "Beliz_forestbandos_10":
			dialog.text = "그럼 동굴로 와라. 동굴이 두 개 있다. 우리가 마지막으로 만났던 곳까지 정글로 들어가서, 왼쪽 길로 가라. 사흘 뒤 자정부터 한 시까지 동굴 입구에서 모인다. 알겠지? 네가 얌전히 굴면 우리 패거리에 받아줄 거다. 하지만 명심해라 – 마을에서 뭐라도 떠벌리면 끝장이다. 내 손은 길거든.";
			link.l1 = "이제 그만 좀 겁주라고. 알았어. 물고기처럼 조용히 있을게. 사흘 뒤에 기다려, 내가 갈 테니까. 쉬운 돈은 사랑이지!";
			link.l1.go = "Beliz_forestbandos_11";
		break;
		
		case "Beliz_forestbandos_11":
			dialog.text = "좋아, 이 친구야. 이제 경비병들이 오기 전에 꺼져라. 우리도 떠날 거다.";
			link.l1 = "또 보자고, 친구...";
			link.l1.go = "Beliz_forestbandos_12";
		break;
		
		case "Beliz_forestbandos_12":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Beliz_Jungle_01", "reload3_back", false);
			LocatorReloadEnterDisable("Beliz_CaveEntrance_2", "reload1_back", true); // закрываем пещеру
			SetFunctionTimerCondition("Caleuche_CaveOpen", 0, 0, 1, false); // таймер
			SetFunctionTimerCondition("Caleuche_BelizbandosClear", 0, 0, 4, false); // таймер
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			for (i=1; i<=6; i++)
			{
				if (GetCharacterIndex("Beliz_forestbandos_"+i) != -1)
				{
					sld = characterFromId("Beliz_forestbandos_"+i);	
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, "TMP_FRIEND");
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "OpenTheDoors", 20.0);
				}
			}
			AddQuestRecord("Caleuche", "13");
			// костер
			ref location = &Locations[FindLocation("Beliz_Jungle_01")];
			DeleteAttribute(location, "fire");
			sld = ItemsFromID("fire");
			sld.shown = false;
			// пакуем схрон в пещере
			pchar.GenQuestBox.Beliz_Cave_2 = true;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.kaleuche_amulet2 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.suit4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse1 = 7; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.purse2 = 3; // Addon-2016 Jason
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potion2 = 10;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.potionrum = 55;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.indian_3 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.obereg_4 = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.berserker_potion = 1;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry2 = 15;
			pchar.GenQuestBox.Beliz_Cave_2.box1.items.jewelry3 = 33;
			// меняем флаг
			pchar.questTemp.Caleuche.Bandos = "know";
			SaveCurrentQuestDateParam("questTemp.Caleuche.belizbandos");
			AddLandQuestMarkToPhantom("beliz_prison", "belizJailOff");
		break;
		
		// спалили бандосы в пещере
		case "Beliz_cavebandos":
			dialog.text = "뭐야! 우리 재산을 넘보겠다는 거냐? 가만두지 않겠다, 이 더러운 벌레 같은 놈아!";
			link.l1 = "방금 누구를 벌레라고 불렀어, 이 쓰레기야?!";
			link.l1.go = "Beliz_cavebandos_1";
		break;
		
		case "Beliz_cavebandos_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Beliz_cavebandos_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			if (MOD_SKILL_ENEMY_RATE > 4)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Beliz_cavebandos_3", "citiz_23", "man", "man", 30, PIRATE, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 30, 70, 70, "blade_10", "pistol1", "bullet", 150);
				ChangeCharacterAddressGroup(sld, pchar.location, "monsters", "monster16");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_CaveBandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// капитан гарпии
		case "reginald":
			dialog.text = "안녕, 동료! 무슨 일로 여기 온 거야?";
			link.l1 = TimeGreeting()+", Jackson 나리. 드디어 당신을 찾아서 기쁩니다.";
			link.l1.go = "reginald_1";
			DelLandQuestMark(npchar);
		break;
		
		case "reginald_1":
			dialog.text = "'잭슨 나리', 하하! 솔직히 말해서, 나도 곧 그렇게 불릴 것 같아. 이 빌어먹을 회사에서 쉬지도 못하고 일하고 있거든... 하지만 돈은 잘 줘, 아주 잘 줘!.. 그런데, 무슨 일로 왔어, 친구?";
			link.l1 = "우리 둘 다 아는 등대지기가 자네가 고대 인디언 부적을 가지고 있다고 하더군. 그동안 쓸 일이 없었을 것 같은데, 나는 그게 꼭 필요하네. 나에게 그걸 팔았으면 하네.";
			link.l1.go = "reginald_2";
		break;
		
		case "reginald_2":
			dialog.text = "아, 내가 그 은퇴한 보선장한테 물어봤던 그 화려한 장신구 말이지? 그래, 친구, 네 말이 맞아. 사실 쓸모는 전혀 없었고, 그냥 보기만 좋더라고.";
			link.l1 = "그거 얼마에 팔 생각이야?";
			link.l1.go = "reginald_3";
		break;
		
		case "reginald_3":
			dialog.text = "있지, 약간 문제가 있어... 설명할게. 지금은 그걸 가지고 있지 않아. 쓸 일이 없을 것 같아서, 해안에 있는 내 짐들 사이 내 상자에 두고 왔거든.";
			link.l1 = "아, 그래서 아직도 그런 거였군... 뭐, 됐다. 그냥 네 상자에 가서 내가 부적을 사면 되겠지. 그게 전부야. 어디에 두었냐?";
			link.l1.go = "reginald_4";
		break;
		
		case "reginald_4":
			dialog.text = "그렇게 간단한 일은 아니야. 내 상자는 바베이도스에 있는 등대 탑에 있고, 내가 없을 때 아무도 손댈 수 없도록 안전하게 잠가 두었지. 그리고 정말 미안하지만, 나는 너와 함께 바베이도스로 갈 수 없어. 네덜란드와 맺은 계약에 따르면 나는 필립스버그와 포트 로얄 사이를 항해해야 하고, 일정도 엄격히 지켜야 해. 바베이도스는 그 항로와는 전혀 상관없는 곳이야.";
			link.l1 = "그래서 우리가 뭘 할 수 있겠어? 난 정말, 진심으로 그 부적이 필요해!";
			link.l1.go = "reginald_5";
		break;
		
		case "reginald_5":
			dialog.text = "흠... 글쎄, 한 가지 방법이 있긴 하지. 내가 내 궤짝 열쇠를 주고, 너는 혼자 바베이도스로 가는 거야. 하지만 그 안에 든 모든 것에 대해 나에게 보상을 해야 하고, 그래야 그것들을 가질 수 있어. 불신해서 미안하지만, 이해해 줘야 해. 나는 너를 처음 보거든.";
			link.l1 = "얼마야?";
			link.l1.go = "reginald_6";
		break;
		
		case "reginald_6":
			dialog.text = "오백 금화다. 그 이하로는 안 돼.";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "알겠어! 여기 네 금화다.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "흠... 지금 내게 그렇게 많은 두블룬은 없어.";
			link.l2.go = "reginald_7";
		break;
		
		case "reginald_7":
			dialog.text = "그럼 돈을 마련하면 다시 나를 찾아오게. 한 번 나를 찾았으니 또 찾을 수 있을 거야. 나는 당분간 세인트 마틴과 자메이카 사이를 항해할 테니.";
			link.l1 = "좋아, 거래하자.";
			link.l1.go = "reginald_8";
		break;
		
		case "reginald_8":
			DialogExit();
			NextDiag.CurrentNode = "reginald_9";
			npchar.DeckDialogNode = "reginald_9";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "reginald_9":
			dialog.text = "또 왔군, 친구? 500닢 있나?";
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "그래. 여기 네 금화다.";
				link.l1.go = "reginald_10";
			}
			link.l2 = "아직 아니지만, 노력하고 있어.";
			link.l2.go = "reginald_8";
		break;
		
		case "reginald_10":
			RemoveDublonsFromPCharTotal(500);
			DelLandQuestMark(npchar);
			
			dialog.text = "좋아! 그리고 여기 네 열쇠다. 부탁이 하나 있는데, 안에 있는 걸 다 가져간 뒤에는 열쇠를 자물쇠에 꽂아 두었으면 한다. 새 자물쇠랑 열쇠를 맞추는 건 정말 번거롭거든.";
			link.l1 = "좋아.";
			link.l1.go = "reginald_11";
		break;
		
		case "reginald_11":
			dialog.text = "그럼 행운을 빌지, 친구! 좋은 항해 되라!";
			link.l1 = "당신도 마찬가지요... 좋은 항해 되시오, Jackson 나리!";
			link.l1.go = "reginald_12";
		break;
		
		case "reginald_12":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_SpawnItemsInTheChest");
			AddQuestRecord("Caleuche", "20");
		break;
		
		case "Caleuche_Reginald_21":
			dialog.text = "뭘 원해서 이러는 거지? 여긴 네덜란드 서인도 회사의 배다. 이런 짓은 그냥 넘어가지 않아. 그들은 너희 같은 족속을 지구 끝까지 쫓아가서라도 응징할 거다.";
			link.l1 = "난 네덜란드 놈들이나 그 무역회사엔 전혀 관심 없어. 내가 찾는 건 오래된 인디언 부적이야, 그리고 그걸 네가 갖고 있다는 걸 알아 – 아니면 예전에 가졌던가.";
			link.l1.go = "Caleuche_Reginald_22";
		break;

		case "Caleuche_Reginald_22":
			dialog.text = "미쳤구나! 고작 장신구 하나 때문에 배를 공격하다니?";
			link.l1 = "닥치고 내놔. 그러면 살려줄지도 몰라.";
			link.l1.go = "Caleuche_Reginald_23";
		break;

		case "Caleuche_Reginald_23":
			dialog.text = "젠장... 나 그거 가지고 다니지 않아. 바베이도스에 있어.";
			link.l1 = "그럼 네 허접한 배는 지금 당장 바다 밑으로 가고, 넌 내 선창에서 쥐들과 같이 지내게 되겠지. 가는 동안 네가 그걸 어디서 찾을 수 있는지 죄다 털어놓을 시간은 충분할 거다.\n그리고 명심해라—우리 배에는 아무리 머리가 굳은 놈이라도 비밀을 다 불게 만드는 녀석들이 있으니까... 상냥함 따윈 필요 없어.";
			link.l1.go = "Caleuche_Reginald_24";
		break;

		case "Caleuche_Reginald_24":
			dialog.text = "그럴 필요 없어. 등대에 있는 상자 안에 있어. 잠겨 있지. 여기 열쇠야.";
			link.l1 = "똑똑한 선택이군, 친구. 네 동료들도 너처럼 머리를 썼으면 좋았을 텐데... 그랬다면 내 손에 피 묻힐 일도 훨씬 줄었을 거야.";
			link.l1.go = "Caleuche_Reginald_24_1";
			link.l2 = "현명한 선택을 했군. 하지만 말이지... 널 살려둘 순 없어. 넌 곧장 그 네덜란드 상인들에게 달려가겠지, 난 그 녀석들 주목을 받고 싶지 않거든.";
			link.l2.go = "Caleuche_Reginald_24_2";
		break;
		
		case "Caleuche_Reginald_24_1":
			dialog.text = "저 상자에는 내가 네덜란드 놈들 밑에서 수년간 벌어들인 모든 게 들어 있지...";
			link.l1 = "그럼 이렇게 하자. 보물상자는 내 거고, 네놈 목숨은 건지는 거다. 괜찮지...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_EndFightWithReginald");
		break;
		
		case "Caleuche_Reginald_24_2":
			dialog.text = "으르릉...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Caleuche_KillToReginald");
		break;
		
		// монах в Виллемстаде
		case "monk_caleuche":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("villemstad");
			npchar.lifeday = 1;
			dialog.text = "안녕하세요, 선장님 "+GetFullName(pchar)+" 윌렘스타트에 오신 것을 환영하오.";
			link.l1 = "안녕하세요, 신부님. 저는 신부님을 기억하지 못하겠는데요. 우리 서로 아는 사이인가요?";
			link.l1.go = "monk_caleuche_1";
		break;
		
		case "monk_caleuche_1":
			dialog.text = "당신 배가 정박하자마자 당신에 대해 알아봤소. 그리고 이제 당신에게 도움을 청해도 될 것 같소.";
			link.l1 = "아주 흥미롭군. 그런데 왜 나지?";
			link.l1.go = "monk_caleuche_2";
		break;
		
		case "monk_caleuche_2":
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				dialog.text = "그대는 자유주 공화국을 위해 많은 일을 했으니, 지금 회사에서도 평판이 좋고 총독과도 친구지. 나는 이미 여러 당국에 청원을 넣었으나 거절당했네. 하지만 그대처럼 고귀한 분이라면 우리 주님의 종이 드리는 소박한 부탁을 거절하지 않을 것이라 믿고 있네.";
			}
			else
			{
				dialog.text = "그건 당신이 우리 총독의 부하가 아니기 때문이오. 당신은 회사 일을 하는 것도 아니고, 우리 군대와도 관련이 없지. 그렇지 않았다면, 아마 나를 성가신 파리쯤으로 여기고 그냥 무시했을 거요. 이미 여러 관청에 호소했지만 모두 거절당했으니 말이오.";
			}
			link.l1 = "좋아, 그럼. 무슨 부탁이냐?";
			link.l1.go = "monk_caleuche_3";
		break;
		
		case "monk_caleuche_3":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "은행 뒤쪽에 집이 하나 있어. 그 집에 살던 여자가 아주 수상한 놈한테 방을 세줬는데, 그 자는 이곳 사람이 아니고, 네덜란드인도 아니었지. 그래서 우리 신부님, 신부\n "+sld.name+", 그를 알아본 사람이 있었지\n그는 조아킴 메리먼, 포르투갈 사람으로, 이단심문소에 의해 마술과 사악한 힘과의 거래 혐의로 기소된 자야. 그는 신세계에서 이단심문소를 피해 숨어 지냈지. 알다시피, 스페인 놈들은 미운 놈을 이단이나 마녀로 몰아 화형에 처하곤 하지. 하지만... 이번엔 그들이 옳았어. 메리먼은 진짜 흑마법사야\n그래서 한동안 윌렘스타트에 살다가, 나타난 것만큼이나 갑자기 사라졌지. 그리고 얼마 후, 그에게 방을 빌려줬던 여자가 그 집을 나오는 걸 아무도 본 적이 없어. 단 한 번도! 그리고 그 후로 어디서도 그 여자를 본 사람이 없지\n밤이면 시민들이 가끔 2층 창문에서 붉고 푸른 빛이 번쩍이는 걸 보고, 이상한 소리, 마치 사악한 비명 같은 소리를 듣는다고 해. 신부님 "+sld.name+" 사령관에게 호소했지. 그는 병사 네 명으로 구성된 순찰대를 보냈어. 그들이 집을 수색했지만 아무것도 찾지 못했어. 주인아주머니도, 다른 사람도, 수상한 물건도 전혀 없었지\n그런데도 이상한 일들이 계속 일어나고 있어. 주인아주머니는 여전히 나타나지 않고, 밤이면 그 지옥 같은 불빛이 여전히 보인다고 해. 게다가 최근에 거지 두 명도 실종됐어. 내가 광장 앞에서 그들이 얘기하는 걸 들었는데, 집에 주인이 없는 걸 알고 그곳에 묵기로 했대. 그 이후로 아무도 그들을 본 사람이 없어.";
			link.l1 = "그 집에 들어가서 무슨 일이 있었는지 내가 직접 확인해 보길 바라는 거지?";
			link.l1.go = "monk_caleuche_4";
		break;
		
		case "monk_caleuche_4":
			dialog.text = "그렇소, 나리. 부디 성스러운 교회를 도와주십시오. 사령관은 그의 순찰대가 아무것도 발견하지 못했다며 우리가 헛것을 본다고 하오. 정부 역시 마찬가지 생각이오. 평민들은 자기들에게 명확한 위협이 아니라 여겨서 신경도 쓰지 않소.";
			link.l1 = "흠... 그리고 내가 거기에 밤에 가야 하나?";
			link.l1.go = "monk_caleuche_5";
		break;
		
		case "monk_caleuche_5":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "네, 마인헤르. 낮에는 그곳이 조용해서 군인들이 아무것도 찾지 못했어요. 지휘관도 자기 부하들이 걱정되는 모양이에요; 저라도 그럴 거예요. 하지만 제발 부탁드려요. 신부님 "+sld.name+" 당신에게 감사하고 보상을 줄 것이오. 밤에 그 소굴에 다녀온 뒤, 그에게 거기서 본 것을 꼭 전해 주시오. 우리의 우려가 근거 있다는 걸 장담하오.";
			link.l1 = "알겠어. 생각해 볼게.";
			link.l1.go = "monk_caleuche_6";
		break;
		
		case "monk_caleuche_6":
			dialog.text = "감사합니다, 선장님. 제 소박한 부탁을 거절하지 않으시길 바랍니다. 부디, 우리 주님과 신앙, 그리고 모든 성스러운 것을 위해 해주십시오. 제 축복과 함께 가시길.";
			link.l1 = "...";
			link.l1.go = "monk_caleuche_7";
		break;
		
		case "monk_caleuche_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "none", "", "", "", -1);
			AddQuestRecord("Caleuche", "24");
			if (CheckAttribute(pchar, "questTemp.Caleuche.Skul"))
			{
				if (CheckAttribute(pchar, "questTemp.Caleuche.SolomonSkul")) sTemp = "visit the house of Joaquim Merriman, where, according to him, strange things happen at night. Remembering that special gleam in Merriman's eyes when he looked at the jade skull, I feel a little creepy. It seems that the old Jew could not resist the sum of half a million pesos. Whatever the case, I don`t feel like going to Merriman former abode at night.";
				else sTemp = "visit the house of my old acquaintance Joachim Merriman, where, allegedly, strange things are happening at nights. I still remember that glitter in Merriman's eyes, when he was looking at the skull, and honestly I feel frightened. I am not really fond of the idea to visit his former abode in the night, who knows what kind of devils lurk there.";
			}
			else sTemp = "visit the house at the back of the bank, where some Joachim Merriman had been renting a room. Apparently it is that warlock, of which Tuttuathapak was talking about. According to the monk, strange things are happening in this house in the night. I really feel uncomfortable about visiting the warlock's former home, who knows what kind of devils lurk there.";
			AddQuestUserData("Caleuche", "sText", sTemp);
			i = Findlocation("Villemstad_town");
			DeleteAttribute(&locations[i], "reload.l14.close_for_night");
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1 = "location";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l1.location = "Villemstad_houseSp1_room";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2 = "Hour";
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.start.hour = 1.00;
			pchar.quest.Caleuche_villemstadhouse.win_condition.l2.finish.hour = 3.00;
			pchar.quest.Caleuche_villemstadhouse.function = "Caleuche_CreateJoakimSkel";
		break;
		
		// охотник у пещеры
		case "cavehunter":
			dialog.text = "잠깐만, 친구. 네 목숨이 아깝다면 거기 가지 않는 게 좋겠어.";
			link.l1 = "그래서 무슨 일이야?";
			link.l1.go = "cavehunter_1";
		break;
		
		case "cavehunter_1":
			dialog.text = "날 믿어, 너는 알고 싶어하지 않을 거야. 하지만 죽음이 바로 코앞에 있고, 내가 성경에 맹세하는데 넌 살아서 돌아오지 못할 거다, 네 상상을 뛰어넘는 것들이 있으니까.";
			link.l1 = "그래, 그렇게 말한다면 운명을 시험하지 않겠어. 경고해줘서 고맙다.";
			link.l1.go = "cavehunter_2";
		break;
		
		case "cavehunter_2":
			dialog.text = "천만에. 그 길은 피하도록 해.";
			link.l1 = "...";
			link.l1.go = "cavehunter_3";
		break;
		
		case "cavehunter_3":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_4":
			dialog.text = "그 길은 비켜, 친구.";
			link.l1 = "그래, 기억나...";
			link.l1.go = "cavehunter_4_1";
		break;
		
		case "cavehunter_4_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_4";
		break;
		
		case "cavehunter_5":
			sld = characterFromId("Havana_Priest");
			dialog.text = "거기로 정말 가고 싶은 거야?";
			link.l1 = "물론이지. "+sld.name+", 아바나 교회의 주임 신부께서 저를 이곳에 보냈습니다. 저는 여기서 무슨 일이 일어나고 있는지 확인하고, 적절한 조치를 취해야 합니다.";
			link.l1.go = "cavehunter_6";
			DelLandQuestMark(npchar);
		break;
		
		case "cavehunter_6":
			dialog.text = "여기서 무슨 일이 벌어지고 있는 거지? 네 눈으로 직접 보면 겁에 질려 떨게 될 거다.";
			link.l1 = "걷는 시체들을 말하는 거야?";
			link.l1.go = "cavehunter_7";
		break;
		
		case "cavehunter_7":
			dialog.text = "그래. 그리고 내 말을 믿는 게 좋을 거야.";
			link.l1 = "나도 그 말을 믿네. 이미 빌렘스타트에서 그 불경한 놈을 마주쳐서 없애 버렸지. 이제 저 안으로 들어가서 이 동굴에 숨어 있는 모든 오물을 전부 쓸어버릴 거야.";
			link.l1.go = "cavehunter_8";
		break;
		
		case "cavehunter_8":
			int icpy = GetOfficersQuantity(pchar);
			switch (icpy)
			{
				case 0:
					dialog.text = "거길 혼자 갈 생각이야? 넌 죽은 목숨이야, 친구. 거기 그놈들이 얼마나 많은지 너 전혀 모르는구나. 뭐, 꼭 가야겠다니 가라. 난 네 영혼의 평화를 위해 교회에 가서 촛불이나 켤게.";
					link.l1 = "나를 너무 빨리 묻으려 들지 마라. 나는 더한 것도 겪어봤다.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 1:
					dialog.text = "너희 둘뿐이야? 그걸로는 멀리 못 가. 저 바깥에 그 괴물들이 얼마나 많은지 너희는 전혀 몰라. 그건 자살 행위야.";
					link.l1 = "너는 우리를 잘 모르는구나, 친구야. 비켜라, 우리가 이 더러운 소굴을 깨끗이 쓸어버릴 테니.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 2:
					dialog.text = "너희 셋뿐이야? 그걸 하겠다고 덤비는 걸 보니 제법 노련한 싸움꾼들인가 보군. 하지만 그래도 나는 너희가 해낼 수 있을지 걱정된다. 그 동굴 안에 그런 것들이 얼마나 많은지 너희는 전혀 모를 거야.";
					link.l1 = "너는 우리를 잘 모르는구나, 친구. 비켜라, 우리가 이 더러운 소굴을 정화할 테니.";
					link.l1.go = "cavehunter_exit";
				break;
				
				case 3:
					dialog.text = "너희들, 겁쟁이는 아니구나. 하지만 저것들이 얼마나 많은지 정말 모르는 모양이군. 이런 일에는 한 사람 한 사람이 다 중요해. 젠장, 나도 같이 가겠다. 내 머스킷으로 그 놈들을 쏴버릴 거야!";
					link.l1 = "넌 용감한 사람이구나, 친구. 네 도움을 마다하지 않겠어. 가자!";
					link.l1.go = "cavehunter_9";
				break;
			}
		break;
		
		case "cavehunter_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		break;
		
		case "cavehunter_9":
			DialogExit();
			npchar.quest.caleuche = true;
			npchar.dialog.currentnode = "cavehunter_10";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			// закрываем локаторы выхода
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload1_back", true);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload3_back", true);
		break;
		
		case "cavehunter_10":
			dialog.text = "가자! 더러운 언데드 놈들, 죽음을 맞이해라!";
			link.l1 = "...";
			link.l1.go = "cavehunter_10_1";
		break;
		
		case "cavehunter_10_1":
			DialogExit();
			npchar.dialog.currentnode = "cavehunter_10";
		break;
		
		case "cavehunter_11":
			dialog.text = "이야, 정말 대참사였군! 누가 이곳에 이렇게 많은 시체가 숨어 있을 거라고 생각이나 했겠어! 뭐, 이제는 좀 쉴 수 있겠지... 자네를 여기로 보낸 그 신부님께 이 일을 꼭 전해 주게. 자네의 보고를 받고 나면 종교재판소가 이 일의 진상을 밝혀주길 바라네. 죽은 자들을 다루는 건 그들의 일이잖아. 나는 그저 평범한 사냥꾼일 뿐이니까.";
			link.l1 = "반드시 전할게. 도와줘서 고마워, 친구. 너 같은 사람은 드물어, 죽음과 맞서 싸울 용기를 가진 자는 많지 않지! 행운을 빌어!";
			link.l1.go = "cavehunter_exit";
		break;
		
		// солдат в крипте при провале
		case "cryptguard":
			dialog.text = "거기서 움직이지 마! 이곳은 출입 금지야!";
			link.l1 = "에이... 거기 뭐가 있는데?";
			link.l1.go = "cryptguard_1";
		break;
		
		case "cryptguard_1":
			dialog.text = "그곳에서 위험한 흑마법사가 발견되었소. 오직 신부님들과 그들을 동행하는 군인들만 들어갈 수 있소.";
			link.l1 = "알겠소. 그 흑마법사는 체포되었소?";
			link.l1.go = "cryptguard_2";
		break;
		
		case "cryptguard_2":
			dialog.text = "저는 그런 질문에 답할 권한이 없소, 나리. 이제 떠나셔야 할 때요.";
			link.l1 = "알겠어. 행운을 빌게!";
			link.l1.go = "cryptguard_3";
		break;
		
		case "cryptguard_3":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("Caleuche", "31");
			CloseQuestHeader("Caleuche");
			pchar.questTemp.Caleuche = "end";
		break;
		
		// чавинави-вождь
		case "Chavinavi":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_01.wav");
			dialog.text = "가만히 있어라, 인간! 너는 지금 신전의 한가운데에 있고, 이제는 돌아가기엔 너무 멀리 와버렸다.";
			link.l1 = "너 누구야?!";
			link.l1.go = "Chavinavi_1";
		break;
		
		case "Chavinavi_1":
			dialog.text = "나는 차비나비의 족장이며, 이 신성한 장소의 수호자이자 지킴이이다.\n이 사원에 들어온 자는 너만이 처음이 아니지만, 너 이전에는 남자 둘과 여자 하나만이 살아서 들어왔다가 나간 적이 있다.\n그것이 내가 지금 너와 말을 나누는 유일한 이유다.\n여기 왜 왔느냐, 창백한 얼굴아?";
			link.l1 = "나는 여기 고대 유물을 가져왔소, 바로 비취 해골이오. 오십 년 전, 이 유물은 본토 깊숙한 곳의 인디언 사원에서 가져간 것이오. 나는 그 신전을 찾아 유물을 당신들의 신께 돌려주려 했소.";
			link.l1.go = "Chavinavi_2";
		break;
		
		case "Chavinavi_2":
			dialog.text = "네놈들 같은 자에게서 그런 말을 듣다니 이상하군. 난 네 말을 믿지 않아. 너희 창백한 얼굴을 한 자들은 항상 뭔가를 빼앗으러 오지만, 절대 아무것도 돌려주지 않지.";
			link.l1 = "나는 거짓말하지 않아. 내가 해골을 돌려주면 카리브 해를 공포에 몰아넣는 유령선 선장에게 걸린 저주가 풀릴 것이고, 그는 다시 죽을 수 있는 인간이 될 거야. 그리고 나는 그를 세상에서 영원히 없애버릴 거다.";
			link.l1.go = "Chavinavi_3";
		break;
		
		case "Chavinavi_3":
			dialog.text = "우리 신께서 그 저주를 풀어주실 거라고 어떻게 아는 거지, 창백한 얼굴아? 우리 신이 너한테 말씀이라도 하시더냐?";
			link.l1 = "아니. 나는 투투아타팍이라는 위대한 주술사의 조언을 듣고 여기 왔다네. 그가 말하길, 해골이 저주의 열쇠이고, 이곳이 카리브에서 유일한 사원이라 했지. 그리고 있잖아, 나는 그가 정말로 과거의 영혼들과 대화할 수 있다고 생각해. 어쩌면 자네, 재규어 전사들의 추장인 자네와도 말이야.";
			link.l1.go = "Chavinavi_4";
		break;
		
		case "Chavinavi_4":
			dialog.text = "네 말이 놀랍구나, 창백한 얼굴이여. 하지만 아직 너를 완전히 믿을 수는 없다. 그래도 네가 우리 유물을 돌려주려고 이 사원에 왔다면, 분명 우리 주술사가 이곳과 그 창조, 역사, 그리고 이곳에 사는 이들에 대해 말해주었을 터이다\n그렇다면 내 질문에 모두 쉽게 답할 수 있을 것이다. 그러면 네가 내게 진실했음을 인정하고, 통과를 허락할 뿐만 아니라 상도 내리겠다.";
			link.l1 = "그럼 물어봐!";
			link.l1.go = "question1";
		break;
		
		case "question1":
			dialog.text = "나는 차비나비와 재규어 전사의 족장이오. 천 년 전에는 인간이었으나, 이제 이 방에서 신성한 임무를 수행하고 있소. 어느 신이 나를 명령하는가?";
			link.l1 = "미클란테쿠틀리.";
			link.l1.go = "question1_l";
			link.l2 = "쿠쿨칸.";
			link.l2.go = "question1_l";
			link.l3 = "윰 시밀.";
			link.l3.go = "question1_r";
			link.l4 = "인티.";
			link.l4.go = "question1_l";
			link.l5 = "카우일.";
			link.l5.go = "question1_l";
		break;
		
		case "question1_r":
			dialog.text = "너희 창백한 얼굴의 사람들이 오기 전에는, 북쪽의 거대한 눈밭에서 남쪽의 드넓은 평원까지 이 땅 전체가 우리, 한 가족의 형제들에게 속해 있었지...";
			link.l1 = "";
			link.l1.go = "question2";
		break;
		
		case "question1_l":
			dialog.text = "너희 창백한 얼굴의 사람들이 오기 전에는, 북쪽의 거대한 눈밭에서 남쪽의 광활한 평원까지 이 땅 전체가 우리, 한 가족의 형제들인 우리 것이었지...";
			link.l1 = "";
			link.l1.go = "question2";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question2":
			dialog.text = "어느 인디언 부족이 이 사원을 지었지?";
			link.l1 = "잉카.";
			link.l1.go = "question2_l";
			link.l2 = "차빈스.";
			link.l2.go = "question2_r";
			link.l3 = "마야.";
			link.l3.go = "question2_l";
			link.l4 = "아즈텍.";
			link.l4.go = "question2_l";
			link.l5 = "아라와크.";
			link.l5.go = "question2_l";
		break;
		
		case "question2_r":
			dialog.text = "우리 사람들은 앞으로 나아가 지혜를 얻었고, 새로운 숲과 평야, 섬들을 정복했다네. 이 사원을 세운 이들은 대양 건너 숲에서 온 사람들이었지...\n";
			link.l1 = "";
			link.l1.go = "question3";
		break;
		
		case "question2_l":
			dialog.text = "우리 사람들은 앞으로 나아가며 지혜를 얻었고, 새로운 숲과 평야, 섬들을 정복했다네.\n이 사원을 세운 이들은 큰 바다 건너 숲에서 온 사람들이었지...";
			link.l1 = "";
			link.l1.go = "question3";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question3":
			dialog.text = "그 영광스러운 사람들의 무리를 누가 이끌었지?";
			link.l1 = "위대한 추장님.";
			link.l1.go = "question3_l";
			link.l2 = "위대한 신부님.";
			link.l2.go = "question3_l";
			link.l3 = "위대한 추장의 아들.";
			link.l3.go = "question3_r";
			link.l4 = "위대한 신부의 아들.";
			link.l4.go = "question3_l";
			link.l5 = "그 무리에는 우두머리가 없었다.";
			link.l5.go = "question3_l";
		break;
		
		case "question3_r":
			dialog.text = "인디언들은 용감한 전사이자 여행자로서, 새로운 곳에 정착한 뒤에도 언제나 고향을 사랑하고 경외했지. 그들은 고향에 대한 사랑의 표시로, 고향을 상징하는 새의 형상으로 신전에 조각상을 세웠어. 그게 바로 내 뒤에 있네...\n";
			link.l1 = "";
			link.l1.go = "question4";
		break;
		
		case "question3_l":
			dialog.text = "인디언들은 용감한 전사이자 여행자로서, 새로운 곳에 정착한 뒤에도 언제나 고향을 사랑하고 존경했지. 그들은 고향에 대한 사랑의 표시로, 고향의 상징인 새 모양의 조각상을 사원에 세웠어. 바로 내 뒤에 있지...\n";
			link.l1 = "";
			link.l1.go = "question4";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question4":
			dialog.text = "이 새의 이름이 뭐지?";
			link.l1 = "알바트로스.";
			link.l1.go = "question4_l";
			link.l2 = "이글.";
			link.l2.go = "question4_l";
			link.l3 = "독수리.";
			link.l3.go = "question4_l";
			link.l4 = "로크.";
			link.l4.go = "question4_l";
			link.l5 = "콘도르.";
			link.l5.go = "question4_r";
		break;
		
		case "question4_r":
			dialog.text = "번영의 세월은 지나가 등불의 불꽃처럼 사그라들었고, 생명은 이 섬을 떠나버렸다. 이제 이곳에는 오직 신전만이 남아 고대 인디언들의 위대한 힘을 상기시켜준다. 마지막 샤먼은 용기 있는 자에게 힘을 주고 악한 자를 벌하는 신성한 태양 구슬을 제단 위에 남겼다. 그 구슬은 너보다 먼저 이곳에 온 자가 가져갔다.";
			link.l1 = "";
			link.l1.go = "question5";
		break;
		
		case "question4_l":
			dialog.text = "번영의 세월도 등불의 불꽃처럼 사그라들고, 생명은 이 섬을 떠나버렸소. 이제 이곳에는 고대 인디언들의 위대한 힘을 상기시키는 사원만이 남아 있지. 마지막 주술사가 신성한 태양 구슬을 제단 위에 남겼는데, 그 구슬은 용감한 자에게 힘을 주고 사악한 자를 벌하였소. 그 구슬은 당신보다 먼저 이곳에 온 자가 가져갔소.";
			link.l1 = "";
			link.l1.go = "question5";
			pchar.questTemp.Caleuche.QuestionFail = "true";
		break;
		
		case "question5":
			dialog.text = "그 신성한 구슬의 이름이 뭐였지?";
			link.l1 = "빛나는 태양의 구슬.";
			link.l1.go = "question5_l";
			link.l2 = "태양광의 오브.";
			link.l2.go = "question5_l";
			link.l3 = "한낮의 태양의 구슬.";
			link.l3.go = "question5_l";
			link.l4 = "떠오르는 태양의 구슬.";
			link.l4.go = "question5_r";
			link.l5 = "지는 해의 구슬.";
			link.l5.go = "question5_l";
		break;
		
		case "question5_r":
			if (CheckAttribute(pchar, "questTemp.Caleuche.QuestionFail"))
			{
				PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
				dialog.text = "틀린 대답은 네가 나에게 거짓말했다는 증거다, 백인 놈! 너는 사악한 의도를 품고 왔구나! 신전과 제단의 수호자들을 몰래 빠져나왔고, 문 장치가 어떻게 작동하는지도 알아냈지 - 하지만 나와의 목숨을 건 결투에서 도망칠 순 없을 거다. 죽을 준비나 해라, 창백한 얼굴아!\n";
				link.l1 = "그래, 그렇게까지 원한다면... 네가 얼마나 대단한 전사인지 한번 보자고...";
				link.l1.go = "chavinavi_fight";
			}
			else
			{
				dialog.text = "네가 우리 민족과 내 사원에 대해 아는 것을 보니, 백인아, 네 실력을 인정할 수밖에 없군. 이제야 네 말을 믿겠다. 가서 네가 여기 온 목적을 이루거라. 신성한 유물을 콘도르 앞 받침대, 즉 떠오르는 태양의 구슬이 한때 있던 자리에 올려놓아라\n그리고 다시 내게 돌아오너라. 윰 시밀을 숭배하고, 네 형제들이 훔쳐간 것을 자발적으로 돌려주기로 한 결정을 내가 반드시 보상해 주겠다.";
				link.l1 = "신뢰해 주셔서 감사합니다, 위대한 추장님.";
				link.l1.go = "chavinavi_exit";
			}
		break;
		
		case "question5_l":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_02.wav");
			dialog.text = "틀린 대답은 네가 나한테 거짓말했다는 증거다, 백인 놈! 너는 나쁜 의도를 가지고 왔구나! 사원과 신전의 수호자들을 몰래 빠져나왔고, 문 장치가 어떻게 작동하는지도 알아냈지. 하지만 나와의 목숨을 건 싸움에서 도망칠 수는 없어. 죽을 준비나 해라, 창백한 얼굴아!\n";
			link.l1 = "그래, 그렇게 나오시겠다니... 네가 얼마나 대단한 전사인지 한번 보자고...";
			link.l1.go = "chavinavi_fight";
		break;
		
		case "chavinavi_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_group_Delete("EnemyFight");
			DialogExit();
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Caleuche_TopChavinaviDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "chavinavi_exit":
			DialogExit();
			sld = ItemsFromID("SkullAztec");
			sld.shown = "0";
			sld.useLocation = "KhaelRoa_Treasure_Alcove";
			sld.useLocator = "button01";
			LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "Chavinavi_5":
			PlaySound("Voice\English\LE\Chavinavi\Chavinavi_03.wav");
			dialog.text = "네가 약속한 대로 했구나, 창백한 얼굴. 네 형제들 대부분처럼 거짓말쟁이가 아니라서 다행이야. 나도 내 약속을 지키겠다. 자, 이 선물을 받아라 – 재규어 전사들의 힘의 상징이다. 유움 시밀께서 직접 이 가죽에 자신의 힘을 담아주셨다.";
			link.l1 = "이런 젠장! 진짜 멋지구나!";
			link.l1.go = "Chavinavi_6";
		break;
		
		case "Chavinavi_6":
			GiveItem2Character(pchar, "KhaelRoa_item");
			Log_Info("You have received jaguar's pelt");
			PlaySound("interface\important_item.wav");
			dialog.text = "이건 평범한 가죽이 아니야. 이걸 입으면 재규어 전사의 힘을 얻게 되지. 불을 뿜고 납탄을 쏘는 네 무기의 위력이 열 배로 강해질 거고, 적들의 시체로 전장을 뒤덮을 수 있을 거다\n하지만 유믹 시밀이 이 가죽에 담아둔 힘을 필멸자는 감당할 수 없어. 한 번 그 힘을 풀어놓으면, 다음 자정까지만 네 곁에 머물다가 사라질 거다. 조심해라, 창백한 얼굴이여. 하찮은 싸움에 이 힘을 낭비하지 마라.";
			link.l1 = "고마워! 적들에게 완전히 밀릴 때만 이걸 쓸게.";
			link.l1.go = "Chavinavi_7";
		break;
		
		case "Chavinavi_7":
			dialog.text = "이제 가거라. 그리고 네 형제들에게 이 신성한 방의 평온을 침범하지 말라고 경고하라. 재규어 전사들은 창백한 자들에게는 자비도, 용서도 베풀지 않는다.";
			link.l1 = "안녕히 계시오, 족장님.";
			link.l1.go = "Chavinavi_8";
		break;
		
		case "Chavinavi_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			n = 1;
			if (MOD_SKILL_ENEMY_RATE > 2) n = 3;
			if (MOD_SKILL_ENEMY_RATE > 4) n = 5;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("TopChavinavi_"+i);	
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Caleuche", "38");
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeIndianRelation(10.0);
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
