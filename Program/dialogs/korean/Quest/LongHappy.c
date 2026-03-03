// диалоги персонажей по квесту Долго и счастливо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
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
			dialog.text = "무슨 일이야?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
		break;
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "드 모르 나리, 이런 행운이! 몇 달 동안 당신을 찾아다녔소!";
			link.l1 = "내 사랑, 나는 가짜 지도나 수상한 정보, 집에서 만든 럼주 따위는 안 사. 고맙지만 사양할게! 아니면 네가 현상금 사냥꾼이냐? 내 목 값이 지금은 얼마쯤 되지?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "오, 나리, 나는... 나는 잡동사니를 팔지도 않고 사람을 죽이지도 않소 - 칼에 손대지 마시오, 그럴 필요 없소, 해칠 생각은 없으니! 모든 게 훨씬 평범하오 - 나는 사신선의 선장이오. 우편물을 배달하지. 그리고 당신에게 중요한 편지가 있소!";
			link.l1 = "편지라고? 누가 보낸 건지 물어봐도 되겠나?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "한 수도원장이 내게 이것을 건네주며 꼭 드 모르 선장에게 직접, 손에서 손으로 전해 달라고 부탁했소. 나는 이미 당신을 찾을 희망을 다 잃고 생피에르 항구 사무실에 맡기려던 참이었는데, 이런 행운이! 여기 계시다니!";
			link.l1 = "그래, 여기 있어. 기다리고 있었어 - 편지를 줘.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "문제가 하나 있소... 아빠트가 배달비는 받는 사람이 내야 한다고 했소. 그래서 자네가 9,200페소를 내야 하오.";
			link.l1 = "그 정도 돈이면, 바다 한가운데서 내 선실까지 아침 커피와 함께 직접 가져다줬어야지! 편지는 네가 가지도록 해.";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "내가 왜 우편 배달 일을 안 했을까?! 해적질보다 훨씬 이득인데! 자, 여기 은화다, 자네. 봉투 내놔.";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "거래하게 되어 반가웠소! 베누아 아빠트께서 안부를 전하셨소! 안녕히 가시오, 드 모르 나리!";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "원하시는 대로 하겠습니다. 봉투는 항구 사무실에 두고 가겠습니다. 하지만 가격에 영향을 줄 테니 미리 말씀드립니다. 그리고, 베누아 아빠트께서 당신께 안부를 전하셨습니다.";
			link.l1 = "베누아 아빠트의 편지? 왜 처음부터 말하지 않았어! 중요한 거잖아!";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "그러니 항만 관리인에게서 받아 가. 미리 대출받는 것도 잊지 말고. 안녕히 가시오, 드 모르 선장.";
			link.l1 = "너보다 더 진실한 해적들도 내가 봤다. 행운을 빌어, 내 사랑.";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "신부님, 오늘은 평소보다 일찍 오셨군요. 부디, 호위가 기다리고 있습니다. 그리고 당신, 드 모레 나리 - 빈첸토 신부께서 당신이 도시에 있다는 소식을 듣고 저녁 식사에 함께해 주시길 청하셨습니다.";
			link.l1 = "유감이지만 종교재판관께서는 혼자 식사하셔야 할 것 같군. 이게 그분의 식욕을 망치지 않길 바라지. 그리고 베누아 아빠트도 그분 곁에 있지 않을 거야. 내가 누군지 알 테니 충고하지. 우리 그냥 조용히 지나가게 해주고, 팔로티 신부께 안부 전해줘.";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
			{
				Notification_Reputation(true, 81, "low");
				dialog.text = "그래, 자네에 대해 많은 이야기를 들었지. 그리고 자네가 고집을 부리더라도 도시를 피바다로 만들지 말라는 명확한 지시를 받았네. 통과해도 좋다. 하지만 빈첸토 신부께서... 불만스러워하실 거야. 이 점 명심하게.";
				link.l1 = "이성적으로 행동하셨군요, 나리. 신부장님의 실망에 마음이 아프지만, 어떻게든 살아남겠지요. 좋은 저녁 되십시오!";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				Notification_Reputation(false, 81, "low");
				Notification_Reputation(false, 19, "high");
				dialog.text = "그래, 너에 대해 들은 적 있지... 아주 흥미로운 이야기들이더군. 하지만 이런 초대를 거절하는 건 건강에 해로워, 나리. 그리고 빈첸토 신부의 손님을 납치하는 것도 마찬가지지. 놈들을 잡아라!";
				link.l1 = "모두가 각자의 선택을 했군. 이렇게까지 되어 유감이오. 무기를 들어라, 나리!";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "Charles, 축하하네! 있잖아, 나는 예전부터 자네가 참 마음에 들었고, Helen은 내게 딸 같은 아이라서 둘 다 정말 기쁘네. 젠장... 교회에서 눈물 한 방울 흘리는 게 내 평생 소원이었지. 내가 늙은 건가, 뭐지?";
			link.l1 = "모든 게 괜찮아, Jan, 나 거의 제단에서 울 뻔했어. 아마 향 때문이겠지?";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "그래, 장뇌, 젠장. 눈이 따갑고 코가 간지러운 이유가 뭔지 계속 궁금했지! 좋아, 샤프타운에서 얘기 좀 하자고, 글래디스를 안아주고 나머지한테 가자. 쟤네 얼굴 좀 봐라, 마치 우리가 베스트팔렌 조약이라도 체결하는 것 같잖아.";
			link.l1 = "와줘서 고맙네, Jan. 자네를 보니 기쁘고, Helen에게도 큰 의미가 있네.";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "드디어 왔군, Charles! 내 코르벳이 너보다 거의 하루 먼저 도착했어 – 자랑할 만한 일이잖아.";
			link.l1 = "천만에, Jan. 그런데 Gladys랑 네 아내는 어디 있지?";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "글래디스는 상선에 태워 블루벨트로 돌려보냈어 – 이런 화려한 파티들을 그녀가 못마땅해하거든. 조안나는 올 수 없었어 – 아, 마르티니크에서 너한테 말할 시간이 없었지! 상상해 봐 – 내가 이 나이에 합법적인 아버지가 된다니, 어때? 있잖아, 네가 서두르면 우리 자식들 나이도 거의 비슷하겠는걸, 하하하!";
			link.l1 = "얀, 축하한다, 좋은 소식이군! 한잔해야지!";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "당연하지! 하지만 먼저, 너희 부부를 위해! 이봐, 거기 조용히 해!!! 늙은 숲의 악마가 한마디 해야겠으니!\n음흠... 그러니까, 우리 사랑하는 드 모르 나리와 마담... 젠장! 이렇게는 말을 못 하겠군! 샤를, 헬렌 - 너희 둘은 내게 내 자식이나 다름없어. 그리고 이 방에 있는 누구도 너희의 결혼을 기뻐하지 않을 사람은 없다는 걸 알아! 그러니 우리 모두, 형제들이여, 우리의 충직한 친구들의 행복을 위하여, 그들의 돛에 순풍이 불기를, 그리고 서로를 향한 그 마음만큼 강한 행운의 여신의 사랑을 위하여, 한잔하세!!! 건배!";
			link.l1 = "건배! 고마워, Jan... 어이, 이 럼은 평소보다 훨씬 독하잖아... Nathan이 뭘 섞은 거야?";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "나도 잘 모르겠지만, 맞는 말인 것 같아. 올드 호크는 술에 관해서는 대체로 전문가지. 자, 가서 다른 사람들에게 가 봐. 나는 술을 만들어야 해, 배불리 마시고 싶어하는 백 명은 족히 되는 놈들이 기다리고 있으니까.";
			link.l1 = "포레스트 데빌이 술을 따르고 있다니, 정말 볼만하군! 파티 준비를 맡아줘서 고맙다. 내가 한 바퀴 돌고 나면 꼭 다시 올게 – 어쩌면 다른 누군가도 도움이 필요할지 모르니까.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "다 괜찮아, Charles?";
			link.l1 = "완벽해, Jan!";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "드디어 왔군! 마르티니크에서는 어땠어? 이제 네 인생이 영원히 바뀌었다고 느끼나?";
			link.l1 = "훨씬 이전에 바뀌었어, 얀. 하지만 모든 게 놀랄 만큼 잘 풀렸지. 요한나는 어디 있고...";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "헬렌? 그 아가씨는 우리가 무슨 일을 꾸미는지 알자마자 곧장 배를 띄워서 수평선 너머로 떠났어. 너한테 온갖 따뜻한 축하 인사를 전하긴 했지만... 그래도 네가 그 아이 마음을 아프게 했지, 정말로. 하지만 괜찮을 거야, 다 젊음이란 게 그런 거니까.";
			link.l1 = "글쎄, 마음이 원하는 건 어쩔 수 없지, 이해하지?";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "그래. 뭐, 요한나는 못 왔어. 상상해 봐—내가 이 나이에 합법적인 아버지가 된다니, 어때? 있잖아, 네가 서두르면 우리 애들 나이도 비슷해질 거야, 하하하!";
			link.l1 = "얀, 축하하네, 좋은 소식이군! 한잔해야겠어!";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "당연하지! 하지만 먼저, 너와 네 반쪽을 위해! 이봐, 거기 조용히 해!!! 늙은 숲의 악마가 한마디 해야겠군!\n찰스와 메리, 지금 모든 형제단이 너희를 위해 잔을 들고 있다! 진정한 친구의 행복은 바다늑대 누구의 영혼도 기쁘게 하지, 스페인 금화의 화려함만큼이나 말이야, 하하! 순풍을 타고 가족의 항해에 행운이 함께하길!!! 건배!";
			link.l1 = "건배! 고마워, Jan... 어이, 이 럼은 평소보다 훨씬 독하잖아... Nathan이 뭘 섞은 거야?";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "나도 잘 모르겠지만, 꽤 맞는 말인 것 같아. 올드 호크는 술에 관해서는 전문가거든. 자, 다른 놈들한테 가 봐. 나는 술에 목마른 백 명쯤 되는 녀석들을 위해 술을 만들어야 하거든.";
			link.l1 = "이 선술집은 이름을 꼭 바꿔야겠어 - '숲의 악마가 직접 여기 카운터 뒤에 서 있었다'로 말이야! 고마워, 얀. 모두와 얘기만 끝나면 꼭 다시 올게. 혹시 누군가 도움이 필요할지도 모르니까.";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "잘 지내고 있나, Charles? 결혼식은 어때?";
			link.l1 = "참 훈훈하군, 얀. 우리 모두를 여기까지 데려올 수 있어서 기쁘네. 호크의 럼주 통도 바닥을 드러내기 시작한 것 같지 않아?";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "그래, 맞아! 자, 이제 네가 가져온 걸 열 시간이다. 그리고 한 가지 더 - 처음에 나를 도와줬던 녀석들이 뒷방에서 너무 취해버렸어. 신랑, 너는 아직 멀쩡해 보이니 셰리 한 상자 좀 가져다줄 수 있겠나?";
			link.l1 = "그래, 어디로 가야 하는지만 말해. 가는 길에 정신 멀쩡한 놈들 좀 만나서 도와달라 해야지. 뭐, 내 부하들 대부분은 이미 술에 잔뜩 취했겠지만.";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "와인은 조선소 지하 저장고에 보관했지, 기억나? 호크가 저쪽 복도 끝에 두라고 했어, ''명절까지 아껴두자''고 말이야. 또 거기 온도랑 습도가 완벽하다고, 와인 저장고로 딱이라고 하더라. 뭐, 진짜 잘난 척하는 놈이지.";
			link.l1 = "그는 옳은 결정을 내렸어, Jan. 내가 갈게. 하지만 먼저, 내 아내를 봤는지 말해 줘.";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "그녀랑 대니는 어디론가 갔어. 여자들끼리 얘기하게 두라고, 찰스. 우리는 진짜 파티를 시작해야지. 내가 음식 준비하는 동안 너는 지하 저장고로 가. 곧 양갈비 대신 숯을 먹게 생겼으니까!\n";
			link.l1 = "좋아, 너는 고기를 구해 와. 나는 우리 와인을 가져올게.";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "찰스, 네이선, 무슨 일이야, 또 술 마시고 싸움이라도 벌인 거야?!";
			link.l1 = "아니, 얀, 우리 감옥에서 무장 커터들과 함께 싸웠잖아. 놈들은 처리했지만, 그 자들은 정찰병일 뿐이었어 - 본대가 바로 뒤에 있어!";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "분대? 무슨 소리야?! 마커스, 이리 와! 찰스, 어서, 다 말해 봐.";
			link.l1 = "내가 말했듯이, 조선소 지하 감옥에 몇 놈이 있어. 무장도 제대로 했더군. 네이선이랑 내가 놈들과 싸워서 기적적으로 전부 쓰러뜨렸지. 하지만 더 많은 놈들이 오고 있어 – 그중 한 놈이 도움을 청하러 갔다는 소리를 들었거든. 그리고, 그래, 그중 한 놈이 자크라는 사람을 언급했어.";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "저놈들 얼굴을 알아보겠어... 이놈, 그리고 문 옆에 쓰러진 저 자식. 자크 더 킨드맨의 졸개들이야. 이름은 기억 안 나지만, 확실해.";
			link.l1 = "그래서 이게 바르바존 때문이란 말이야? 저 자식 미친 거 아냐, 뭐야?!";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "나도 잘 모르겠지만, 킨드맨이 이 기회를 잡아 브레thren의 남작들 사이에서 대대적인 개편을 주도하려는 것 같아.";
			link.l1 = "이번엔 그 자식이 직접 나타나길 바란다 - 내가 얼마나 오랫동안 그놈 몸에 구멍 몇 개 뚫는 꿈을 꿨는지 알아? 망할 놈, 내 결혼식을 망쳐 놓다니, 생각만 해도 열받는다! 움직이자, 거리로 나가자! 손님들에게 제대로 환영을 해주자고!\n";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "그리고 여기 지친 우리의 영웅이 왔군! 하, Charles, 정말 대단했어! Jacques, 저 쥐새끼 같으니! 저 놈이 어떻게 판을 짰는지 봐봐 – 거의 성공할 뻔했잖아!";
			link.l1 = "그래, 아마 잭맨 일을 끝냈을 때 그 자식도 죽였어야 했을 거야. 하지만 이제 끝났어. 바르바존은 죽었다.";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "글쎄, 이게 끝났다고는 할 수 없지 - 우리의 삶은 계속된다! 하지만 나는 완전히 녹초가 됐어. 불타는 배에서 바다로 뛰어들어 한 시간이나 상어를 조심하며 헤엄쳐서 해안까지 오는 건 내 나이에 너무 힘들어. 아직 럼주가 좀 남아 있길 바란다...\n";
			else dialog.text = "글쎄, 이게 끝났다고는 할 수 없지 - 우리의 삶은 계속된다! 젠장, 열 살은 젊어진 기분이야! 저렇게 싸워본 건 정말 오랜만이군! 난장판 속에서 럼주랑 와인 창고가 털리지 않았길 바란다 - 제대로 축배를 들어야 하니까!";
			link.l1 = "그래, 나도 한잔하고 싶지만, 먼저 관저를 확인해야 해. 네가 들었는지는 모르겠는데...";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "네 인디언 친구 말인가? 그래, 들었어. 어떻게 된 일이야?";
				link.l1 = "그자는 내 아내와 다니엘을 한 놈이 쏜 총알로부터 지키려고 뛰어들었어. 가자, 가면서 설명해 줄게.";
			}
			else
			{
				dialog.text = "네이선 이야기인가? 그래, 들었지. 그런데 어떻게 된 건지는 잘 모르겠더군?";
				link.l1 = "그 자식이 쏜 총알에서 우리 아내들을 지키려고 뛰어들었어. 가자, 가는 길에 얘기해 줄게.";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "기운 내, Charles. 네 부하들 일로 정말 유감이야. 오늘 많은 훌륭한 사내들이 쓰러졌고, 그 한 명 한 명마다 Barbazon 놈이 지옥에서 보일러에 부을 기름이 더 많아지겠지.";
				link.l1 = "말도 안 돼... 젠장! 힘들어, 얀... 이미 친구들도 잃었지만, 도저히 익숙해지질 않아. 더는 계속할 수 있을지 모르겠어.";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "그 조용한 의사 말인가? 미안해, Charles. 정말로. 그는 좋은 사람이었어.";
					link.l1 = "그래, 얀, 나도 그래. 하지만 과학계가 내가 잃은 것보다 훨씬 더 많은 걸 잃은 것 같아. 그는 천재였지... 다른 이들처럼 세련됐고, 하지만... 젠장...";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "your Indian guy";
					else sTemp = "Nathan";
					dialog.text = "글쎄, 이제 끝난 것 같군. 오늘 많은 훌륭한 사내들이 갔지. 그 한 명 한 명마다 지옥에서 바르바존 놈이 자기 보일러에 기름을 더 얻게 될 테지만\n "+sTemp+" 괜찮을 거야, 그게 제일 중요하지.";
					link.l1 = "맞아, Jan. 덕분에 마음이 한결 가벼워졌어. 다른 남작들은 어때? 다들 괜찮아?";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "자크 바르바종의 마지막 더러운 짓거리군. 네 말이 맞아, 우리가 그 자를 더 일찍 죽였더라면 모든 게 달라졌을지도 몰라.";
			link.l1 = "하지만 지난 일을 후회해서 뭐하겠어? 과거는 바꿀 수 없어. 다른 남작들은 어때? 모두 살아남았나?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "아무도 익숙해질 수 없어. 우리 녀석들을 위해 한잔할까? 테이블 위에서 병 하나를 찾았는데, 이 난리통에도 기적적으로 살아남았더라고.";
			link.l1 = "따르라고, 나... 젠장... 천 번이고 젠장할 놈의 세상!";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "그들에 대해 말해 봐. 그 의원은 영리해 보였어. 아주 현명하게 말하더군.";
			link.l1 = "그가 그랬지. 하지만, 유감스럽게도 과학의 세계는 나 하나만 잃은 게 아니야. 그는 천재였어... 그들 모두처럼 세련됐지. 기적의 달인이었어!";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "인디언 남자에 대해서 말인가? 어디서 그를 찾았지?";
			link.l1 = "과달루페 감옥에서 막 도착하자마자 그를 구해냈지. 정말 웃기고 멍청한 이야기야. 그래서 그는 내 곁에 남았어. 내가 자유를 줬지만, 그가 스스로 남기로 한 거지 – 내가 그를 구했으니 평생 내게 빚졌다고 생각했거든. 말수 적고 옷차림도 이상했지만, 어느 기사보다도 충직했어. 게다가 재주도 있었지 – 어떤 거리든 공중에 던진 동전을 머스킷으로 맞출 수 있었거든.";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "글쎄, 그가 네 빚을 갚았으니 더 할 말이 없지. 살았다\n "+sld.name+" 그리고 그 자식에게서 다니엘도 구했지. 내 생각엔, 이렇게 용감한 전사에게 딱 어울리는 결말인 것 같아.";
			link.l1 = "그래, 얀. 전사한 이들의 명복을 빌며 한잔하자... 그들이 평안히 쉬길. 다른 남작들은 어때? 다들 무사한가?";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "이번 밤은 우리에게 큰 대가를 치르게 했어. 브레더런이 이 학살에서 언제 회복할 수 있을지조차 모르겠군. 킨드맨은 공격할 시간과 장소를 완벽하게 골랐지. 거의 성공할 뻔했어—조금만 더 갔으면 전부 끝장날 뻔했지. 그래도 우리가 잃은 건 잃을 수도 있었던 것보단 훨씬 적었어.";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "상어는 지금 의무실에 있어. 그의 배가 24파운드 포탄 세례를 맞았거든. 그는 바다에 내던져져서 갈비뼈 몇 개가 부러지고 바닷물도 좀 마셨지만, 살아 있어. 며칠만 지나면 다시 멀쩡해질 거야.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "베르나르는 긁힌 자국 몇 개만 입었어. 해안을 지키고 지하 묘지를 정리하고 있었거든. 지금은 항구에 있으면서 부상자들을 위한 야전병원을 마련하고, 운이 없던 이들을 위한 장례도 준비하고 있지.";
			else dialog.text = "베르나르는 운이 없었어. 지하묘지에서 공격이 끝난 뒤 집들을 정리하다가 창고에서 그 놈들 무리를 만났지. 총알을 맞았는데, 그것도 머리에 정통으로 맞았어. 안타깝지, 좋은 선장이었는데... 타이렉스가 이 사실을 알면 분노할 거야.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "베르나르는 상처만 몇 군데 났어 – 해안을 지키고 지하 묘지를 정리하고 있었거든. 지금은 항구에 있으면서 부상자들을 위한 병원을 마련하고, 운이 없었던 자들을 위한 장례를 준비하고 있어.";
			else dialog.text = "베르나르는 운이 없었지. 놈은 지하 묘지에서 공격이 끝난 뒤 집들을 정리하다가 창고에서 그 자식들 무리를 만났어. 총알을 맞았는데, 그것도 머리에 정통으로 맞았지. 안타깝군, 좋은 선장이었는데... 타이렉스가 이 사실을 알면 분노할 거야.";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "호크 말이지. 대니가 최소 한 달은 그 녀석을 섬에서 못 나가게 할 거야, 그건 확실해. 머릿속엔 한 가지밖에 없었지... 뭐, 됐어.";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "Marcus는 여전히 변함없이 굳건해. 상륙하자마자 곧바로 이런 더러운 꼴을 허락한 보초놈들 혼을 쏙 빼놓기 시작했지. 아직도 마을의 질서를 바로잡으라고 명령을 내릴 수 있더라고. 의심할 여지 없는 강철 같은 사나이야.";
				link.l1 = "쇠도 저보단 부드럽지. 우리 남작 나리는 과학에 아직 밝혀지지 않은 금속으로 만들어졌나 보군, 하하!";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "마르쿠스의 상황만은 아직 불분명해. 그의 배는 적에게 습격당했지만, 살아남은 자들은 그가 바다로 뛰어내리는 데 성공했다고 주장하고 있어. 나는 이미 장주선을 보내 만을 수색하게 했지. 우리 남작이 그렇게 쉽게 포기하지 않을 만큼 강인하길 바란다.";
				link.l1 = "그거 안됐지만, 아직 그를 애도하긴 이르다. 마르쿠스가 그렇게 쉽게 우리를 포기할 리 없어. 수색 결과를 기다려 보자.";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "마커스는 배가 침몰한 뒤 헤엄쳐서 해안에 도착했지. 뭐, 알다시피 타이렉스가 그런 사소한 일로 익사할 놈은 아니잖아. 지금쯤 저 도시 어딘가에 있을 거야. 아마 이런 더러운 꼴을 못 본 척한 경비병들 혼쭐내고 있겠지. 쇠처럼 강한 사내야, 의심할 여지도 없어.";
				link.l1 = "쇠는 가라앉지. 우리 남작 나리는 과학에도 아직 알려지지 않은 재질로 만들어졌나 보군, 하하!";
			}
			else
			{
				dialog.text = "마르쿠스는 여전히 변함없이 든든해. 상륙하자마자 이 더러운 꼴을 못 본 척한 보초놈들 혼을 단단히 빼놨지. 아직도 마을의 질서를 바로잡으라고 명령을 내릴 수 있으니 말이야. 정말 강철 같은 사내야, 의심할 여지없지.";
				link.l1 = "철도 더 부드럽지. 우리 남작 나리는 과학에 아직 알려지지 않은 금속으로 만들어졌나 보군, 하하!";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "그게 다야. 뭐, 더 나쁠 수도 있었지. 찰스, 네 결혼식조차도... 전투적이었잖아. 중요한 건 너희 둘 다 살아 있다는 거야. 마지막으로 작은 충고 하나 할게... 사랑해라... 그리고 그 사랑을 위해 싸우는 걸 절대 포기하지 마!\n";
			link.l1 = "고맙네, Jan. 모두들, 고마워... 솔직히 말해서, 우리가 축하로 시작했다는 걸 잊고 있었어.";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "그러니, 여기 다시 한 번 상기시켜 주지.";
			link.l1 = "그래, 그건 정말... 난장판 파티였지.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "아, 맞아, 확실히 그랬지, 잠깐만. 뭔가 있는데... 너랑 같이 다니는 인디언 남자가 있었잖아, 맞지? 항상 네 곁에 있거나 누가 너를 노리는 것처럼 주위를 살피더라고. 이상한 옷차림에, 큰 군중 속에서도 아주 눈에 띄었어.";
			link.l1 = "그래, 티칭기투, 이 소동이 시작되자마자 사라졌어. 솔직히 걱정되기 시작하는군. 혹시 아는 거라도 있어?";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "그런 것 같아. 우리 술집 주인이 조카가 납치당했다고 소란을 피웠거든, 공격 전에 말이야. 어떤 인디언이 그녀를 어깨에 메고 마을 동쪽 해안가를 따라 가는 걸 봤다고 하더군. 난 Kindman의 졸개들 중에 인디언은 못 봤지만, 네 얘기를 듣고 생각나서 그냥 입 다물고 있었지. 그를 찾으러 가보는 게 좋을 거야, 뭔가 일이 커지기 전에 말이지. 술집 주인이 먼저 찾으면 죽여버리겠다고 협박하고 있으니까. 그 친구 착한 사람이긴 한데, 조카 일이라면 누구든 머리통을 뜯어버릴 놈이거든.";
			link.l1 = "그래, 어떤 놈인지 나도 알아. 걱정 마, 그리고 고마워, Jan. 바로 가서 그 자를 찾아볼게.";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "음, 대충 이런 거지... 미안해, 내가 말솜씨가 별로라서. 그리고 지금은 더 심해졌어 - 오늘 밤에 모두가 완전히 지쳤거든. 우리 모두 하루 정도는 쉬어야 해 - 그 다음에 앞으로 어떻게 할지 정하자.";
			link.l1 = "맞아, Jan. 나 가야겠어, 머리를 좀 식혀야 하니까.";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "좋아 보이네, Charles. 잘 잤어?";
			link.l1 = "그래, 우리는 마을 외곽에 아늑한 집을 받았어. 어제 일어난 그 모든 광기가 꿈이었나 싶기도 했지. 그런데 네가 여기 있네, 얀. 꼴이 말이 아니구나. 또 무슨 일이 있었던 거야?";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "아, 아니야, 별일 아니야. 아직 잠을 못 잤을 뿐이야. 알잖아... 여기서 벌어진 일들 때문에 도시를 정리하는 게 쉽지 않거든.";
			link.l1 = "대니랑 네이선은 잘 지내? 모두 어디 갔어?";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "쉬고 있어. 건드리지 마, 오늘은 다니가 총을 들고 자겠다고 모두한테 경고했으니까... 도드슨은 바다에 나가서 섬을 지키기 위해 더 많은 배를 구하러 갔고, 다른 사람들은 섬 북쪽에서 죽은 이들을 묻고 있어.";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "마커스는 아직 못 찾았지만, 우리가 처리할 수 있으니 걱정 마. 너는 우리 모두를 위해 정말 많은 일을 했으니, 더 이상 신경 쓰지 마. 티락스는 조만간 돌아올 거야 - 우리가 반드시 찾아낼 테니까.";
			else dialog.text = "마커스는 여기서 일을 마치고 누군가의 루거선을 타고 히스파니올라로 급히 떠났어. 바르바존이 죽은 뒤 생긴 문제들을 해결해야 한다더군. 너와 네 아내에게 안부와 행운을 전한대.";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "그래, 우리 해적 동맹은 이번 타격을 견뎌냈다네. 곧 우리는 예전보다 더 강하게 일어설 것이오. 킨드맨과 잭맨이 너무 오랫동안 우리 단결을 흔들었지만, 이제 그 자들은 사라졌으니 내 마음 깊이 느끼오, 우리가 카리브를 여러 번 뒤흔들게 될 거라고. 법과 왕이 친구가 아닌 자들에게 황금시대가 다가오고 있소, 내 말을 기억하시오.";
			link.l1 = "그거 참 좋겠군. 이제 더 이상 구세계에서 견딜 수 있을지 모르겠어. 여기 왔을 때는 상상도 못 했지, 내가 바다의 자유와 이 거친 석양과 여명의 색에 반하게 될 줄, 세상에서 가장 좋은 여자를 만나게 될 줄, 그리고... 내 목숨을 맡길 수 있는 친구들을 얻게 될 줄 말이야.";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "글쎄, 항로는 알 테니, 마음만 정하면 돼. 우리 집에서는 언제나 환영이야.";
			link.l1 = "고마워, Jan. 나한테 정말 큰 의미야.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "하지만 먼저, 중요한 일이 남아 있네. 샤를, 네가 자는 동안 우리가 모여서 결정했지\n바르바종이 죽었으니, 형제단에 새로운 남작이 필요하거든. 여기 있는 우리 다수의 동의로, 만장일치로 결정됐네. 축하하네 - 이제 네가 르 프랑수아의 새 남작이야. 잠깐만... 이해하지, 자네는 세상 물정에 밝은 사람이니 이 멋진 곳의 일까지 직접 챙길 시간은 없을 테지. 그래서 우리가 믿을 만한 사람을 그 자리에 뒀으니, 자네는 원하는 대로 하면 돼. 다만 기억하게 - 이제 자네의 목소리가 형제단에서 중요한 의미를 가진다는 걸.";
			link.l1 = "얀, 나... 나 할 말을 잃었어... 이건 정말 큰 영광이야, 뭐라 해야 할지 모르겠어...";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "어서 가! 그때 타이렉스 일에서도, 샤프의 유산 사건에서도 네가 완벽하게 실력을 증명했잖아. 넌 신이 내린 축복이야. 너라면 아무것도 달라질 게 없어 – 계획대로 하라구, 네가 없는 동안엔 네 부하가 모든 일을 맡을 거니까.\n유망한 친구가 한 명 있는데, 얀 다비드라는 녀석이야. 버커니어 중 한 명이고, 프랑스 놈인데, 정직하고 머리도 비상해서 너처럼 그걸 잘 써먹을 줄 알아. 다만 얘를 찾으려면 시간이 좀 걸릴 거야 – 스페인 놈들에게 잡혔다던데, 그건 해결할 수 있으니 걱정 마. 내가 얘한테 네 몫을 사업에 익숙해지는 대로 바로 보내라고 확실히 해두지.";
			link.l1 = "정말 이렇게 될 줄은 몰랐지. 뭐, 이미 결심했다면 어쩔 수 없군. 해적 남작 샤를 드 모르!";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "남작 만세! 그 이름을 가질 자격이 있다면 바로 당신이지. 자부심을 가지고 그 칭호를 누리시오, 그리고 잊지 마시오 – 아무리 멋진 제복을 입고 있어도 이제 당신은 우리 중 한 사람이오. 바로 그 아래, 진짜 해적의 심장이 뛰고 있으니.";
			link.l1 = "모르겠네, 아마 네가 과장하는 걸지도... 하지만 네가 나를 믿어준 만큼, 내가 할 수 있는 건 다 해볼게.";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "이제 뭐 할 거야? 유럽으로 돌아가서, 아버지한테 가서, 네 아내를 소개할 생각이야?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "그래, 하지만 먼저 작별을 고해야 할 사람이 있어... 무슨 말인지 알겠지.";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "아직 그렇게 빨리일 필요는 없지. 한 번 더 군도를 항해할 거야, 마지막으로 이 자유의 공기를 마음껏 마시고 싶거든.";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "그래, 배도 있으니 집으로 언제든 돌아갈 수 있겠군.";
			link.l1 = "그러길 바라. 고마워, Jan, 그리고 모두에게도 고맙다. 나중에 보자, 내 오랜 친구! Hawks와 Shark에게도 안부 전해 줘!";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "They deserve";
			else sTemp = "He deserve";
			dialog.text = "그래, 힘들지만 해야 해. 바다로 갈까?";
			link.l1 = "아니, 나는 앤티가로 항해할 거야. "+sTemp+" 잠시나마 우리의 집이 되었던 곳에서 평안히 쉬기를.";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "나 대신 좋은 말도 좀 전해 줘. 그리고 걱정하지 마, 이제부터는 우리끼리도 충분히 해낼 수 있어. 다 잘될 거야.";
			link.l1 = "고마워, Jan. 곧 보자, 내 오랜 친구! Hawks랑 Shark에게도 안부 전해 줘!... 자, 그럼 Antigua로 가는 거군.";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "젊은이, 오늘 너를 다시 보게 되었구나. 네가 헬렌을 위해 해준 일은 아무리 고마워해도 부족할 거다. 앞으로도 계속 그녀를 잘 부탁한다. 만약 그녀의 아버지가 살아 계셔서 이 모습을 보셨다면 얼마나 기뻐하셨을까... 아, 미안하구나.";
			link.l1 = "괜찮아, 글래디스. 오늘 헬렌을 도우려고 군도를 건너왔잖아. 나와 헬렌 둘 다 네가 얀과 함께 와 준 걸 정말 고맙게 생각해, 고마워.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "마우르 나리, 이렇게 친근하게 부르는 것을 용서해 주시오. 하지만 이렇게 말하겠소 - 샤를, 내 친구여, 진심으로 기쁘오! 자네나 신부에게 내가 해줄 수 있는 일이 있다면, 언제든 말만 하게!";
			link.l1 = "감사합니다, 남작 나리. 정말 기쁩니다. 그리고 아버지께서 지참금으로 원하셨던 포도밭에 대해서는, 이제 제가 만회할 수 있을 것 같습니다. 다행히도 신세계에서 지내는 동안 제 재정 상황이 크게 나아졌거든요.";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "그래, 네가 원하는 건 뭐든 살 수 있겠지, 샤를. 실례하마, 내가 대표 아버지로서 한마디 하겠네 - 오늘 나는 내 친한 친구, 재무장관에게 편지를 쓸 생각이야. 네가 선택한 여인에게 귀족 칭호를 내려줄 것이고, 그리고 좋은 영지도 찾아줄 수 있을 것 같네. 예를 들어 가스코뉴에 있는, 빚 때문에 몰수된 영지 중 하나를 그녀에게 소급해서 배정해 주지. 그러면 아무도 몽페르 기사께서 신분 낮은 아내를 얻었다고 감히 말하지 못할 걸세!";
			link.l1 = "나는 그런 소문에 신경 쓸 이유가 없다고 생각하지만, 그래도 고맙소, 남작 나리. 그렇지만 당신도 그래서는 안 되오";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "당연히 그래야지! 이제 가게, Charles, 다른 손님들에게도 신경을 써 주게. 그리고 다시 한 번, 진심으로 축하하네!";
			link.l1 = "아내와 나는 당신께 감사드립니다. 또 뵙겠습니다, 남작 나리.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "마우르 나리, 이렇게 친근하게 부르는 것을 용서해 주시오. 하지만 이렇게 말하겠소 – 샤를, 내 친구여, 진심으로 기쁘오! 자네나 신부를 위해 내가 해줄 일이 있으면 언제든 말만 하시오!";
			link.l1 = "감사합니다, 남작 나리, 하지만 이미 저에게 너무 많은 것을 해주셨습니다. 초대에 응해주신 것만으로도 저희에게는 충분합니다.";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "내가 어찌 대답하지 않을 수 있었겠나, 샤를! 하지만 들어보게 – 자네와 자네의 아름다운 신부에게 걸맞은 선물을 주고 싶은데, 돈이나 칼로 자네가 스스로 얻지 못할 것이 생각나지 않네. 그래서 파리의 재무장관 친구에게 편지를 쓸 생각이야. 자네가 유럽에 도착할 때쯤이면, 드 몽페르 가문이 몽페르 남작 작위로 승격되는 왕실 칙서를 자네가 직접 서명하도록 기다리고 있을 걸세! 아니, 아무 말도 하지 말게, 이 정도는 내가 자네를 위해 해줄 수 있는 최소한이네.";
			link.l1 = "무슨 말을 해야 할지 모르겠어요, 남작님... 아버지가 정말 기뻐하실 거예요. 진심으로 감사드립니다.";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "Charles, 제 진심 어린 축하를 받아주십시오! 당신이 선택한 분은 정말 놀라운 분이군요! 오늘 식민지의 유행이 새로운 방향으로 강한 ... 충격을 받은 것 같습니다. 당신의 독창성은 언제나 저를 매료시켰습니다! 두 분이 영원히 행복하시길 바랍니다!";
			link.l1 = "감사합니다, 남작 나리. 방문해 주셔서 저희에게 큰 영광입니다.";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "어떻게 내가 멀리 있을 수 있겠어, 친구야? 우리는 함께 많은 일을 겪었고, 나는 너를 내 친구라고 부를 수 있어서 자랑스럽다, Charles. 기억해라 - 무슨 일이 있든 내 문은 항상 너에게 열려 있으니.";
			link.l1 = "드 몽페르 가문의 문은 언제나 당신에게 열려 있을 것이오, 남작 나리.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "샤를, 친구여, 오늘은 정말 중요한 날이네. 나를 초대해 함께하게 해줘서 기쁘네. 자네와 나는 참으로 멀고도 험한 길을 걸어왔지. 그리고 마드모아젤의 대리 아버지가 되다니... 부디 용서하게. 마담 드 모르, 내게는 큰 영광이네, 믿어주게. 진심으로 자네의 행복을 빌네! 그리고 제발, 유럽에 갈 계획이 있으면 꼭 알려주게 – 자네의 선택을 받은 이의 대리 아버지로서, 자네 아버지께 결혼에 필요한 모든 예물을 보내드릴 걸세. 믿게나, 아무도 몽페르 기사 나리의 신부가 가난하거나 부족하다고 말하지 못할 걸세!";
			link.l1 = "실례가 안 된다면 여쭙겠습니다, 슈발리에 나리. 몽페르 영지에서 북쪽으로 몇 마일 떨어진 곳에 좋은 포도밭이 있습니다. 그 포도밭은 라 브리뉴 가문 소유이고, 저는...";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "더 이상 말하지 마, 친구, 더 이상 말하지 마! 나는 즉시 리옹에 있는 내 공식 대리인에게 편지를 쓸 거야 – 네가 도착할 때쯤이면 이 포도밭은 네가 고른 사람에게 넘어가 있을 거야.";
			link.l1 = "감사합니다, 슈발리에. 말씀대로 우리... 우정도 참 많은 일을 겪었지요. 그래도 오늘을 함께해 주셔서 정말 기쁩니다. 또 봅시다, 다시 한 번 고마워요!";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "찰스, 친구여, 오늘은 정말 중요한 날이네. 나를 초대해 함께하게 해줘서 기쁘다네.\n우리는 먼 길을 어렵게 걸어왔고, 오늘 그대의 결혼식에 증인이 될 수 있어 내게는 큰 영광이야.\n진심으로 행복을 빌어! 그리고 유럽에 갈 계획이 생기면 꼭 알려주게 – 그대 아버지께 어울리는 결혼 선물을 보내드릴 테니.";
			link.l1 = "이럴 필요까지는 없습니다, Chevalier 나리. 제 초대에 응해 주셔서 감사합니다.";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "내가 말했듯이, 이건 내게 영광이야! 하지만 잠깐만, 친구, 이 기회에 너에게 뭔가를 선물하고 싶어 – 분명 너도, 네가 선택한 이도 마음에 들어할 거야. 뉴기니아 광산에서 나온 아름다운 보석들이야 – 멋진 장식에 세팅해서 마드무아젤 드 모르에게 주면, 왕실 연회에서도 빛날 거야! 물론, 그녀가 드레스를 입도록 설득할 수 있다면 말이지...\n";
			link.l1 = "아, 정말 이러지 마시오, 슈발리에. 다시 한 번 감사하오.";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "찰스, 친구여, 축하를 전하네! 우리는 길고도 험한 길을 함께 걸어왔고, 오늘 이 자리에 있게 되어 진심으로 기쁘네. 우리 주님께서 증인이시니, 그대는 행복을 누릴 자격이 있네! 그 행복을 소중히 여기고 지키게나 – 앞으로도 오랜 세월 행복하길 바라네!";
			link.l1 = "감사합니다, Chevalier 나리, 제 아내와 저는 정말로 감사하게 생각합니다.";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "찰스, 정말 대단한 축하 자리군, 그리고 이렇게 많은 귀한 분들까지! 진심으로 행복과 건강, 그리고 기쁨을 줄 자녀들이 있기를 바라네! 우리 식으로 말하자면 - '고르코'!";
			link.l1 = "고맙소, 파데이. 와 주기로 해 주셔서 영광이오.";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "하지만 왜 이렇게 사람들이 많은지 잘 모르겠네, 마치 우리가 결혼하는 게 아니라 무슨 대단한 거래라도 하는 것 같잖아. 그런데도 내 취향엔 맥주나 보드카가 아직도 부족해... 하하! 뭐, 농담이야, Charles, 왜 그렇게 얼굴이 하얗게 질렸어? 이리 와서 안아 줘, 이 결혼한 선장!";
			link.l1 = "이런 젠장... 페이디, 너 곰만큼 힘세구나!";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("You got three Persian sabres");
			PlaySound("interface\important_item.wav");
			dialog.text = "잠깐만, Charles, 아직 가지 마. 손님이 선물 없이 결혼식에 참석하는 건 예의가 아니지. 자, 이것들을 가져가. 네가 이 칼들을 다 찾아보려고 했던 것도 알고, 그중 몇 개는 분명히 마음에 들어 했지. 그러니 받아 줘. 가문 저택에 걸어두고 Fadey Moskovit을 좋은 마음으로 기억해 줘!";
			link.l1 = "이건 정말 귀한 선물이군! 고맙네, Fadey. 정말 훌륭한 무기들이야. 약속하네, 이 무기들은 반드시 드 몽페르 영지에서 마땅한 자리를 차지하게 될 걸세!";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "Charles, 정말 대단한 축하 자리군, 이렇게 많은 귀한 분들도 오셨고! 진심으로 행복과 건강을 기원하네, 그리고 기쁨을 줄 자식들도 많이 생기길 바라네! 우리 식으로 말하자면, '고르코'! 자, 안아 주게, 이제 유부남 선장!";
			link.l1 = "이런 젠장... 파디, 너 곰만큼 힘세구나!";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "찰스, 이 자리를 놓칠 수 없었지. 진심으로 너와 네 짝에게 축하를 보낸다! 행복하게 살아라! 있잖아, 몇 달 전에 내 딸을 좋은 남자에게 시집보냈는데, 둘이 서로 사랑하더라고. 하지만 솔직히 말하면, 그게 네가 아니라서 좀 아쉬웠어... 뭐, 됐다... 내가 무슨 말을 하는 건지... 어쨌든 축하한다! 오래오래 행복하게 살아라!";
			link.l1 = "고맙네, 프로스페르, 와줘서 기쁘네.";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "축하하오, 선장! 이상한 의식이긴 하지만 아름다웠소 – 티칭기투도 마음에 들어 했소. 하지만 선장이라면 그냥 자기 여자를 납치해서 그 친척들에게 몸값이나 보내는 게 더 나았을 텐데.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "뭐, 어떻게 보면 그렇지, 그냥 형식적인 거야. 고마워, 친구!";
			else link.l1 = "뭐, 어떻게 보면 그렇지, 그냥 형식적인 절차일 뿐이야. 고마워, 친구! 너랑 나는 샤프타운에서 더 많이 얘기하게 될 거야\n그땐 공식적인 일은 훨씬 적고, 진짜 재미있는 시간이 많을 거라고 약속할게!";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "또 불물인가? 티칭기투는 그걸 좋아한다고는 못 하겠어. 차라리 축하 겸 배를 습격하는 게 낫지 않을까, 아니면 적어도 모닥불 주위에서 춤이라도 추는 게?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "나는 끝나기도 전에 모닥불 주위를 춤추는 일은 없었으면 좋겠고, 선상 전투도 피하고 싶어. 좋아, 좀만 더 참자. 이제 조금만 남았으니 바로 선술집으로 가자.";
			else link.l1 = "끝나기 전에 모닥불 주위를 돌며 춤추게 될까 두렵군, 난 승선을 피하고 싶어. 좋아, 조금만 더 참아. 이제 곧 샤프타운으로 바로 출항할 거야.";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "선장님, 다시 한 번 축하드립니다! 티칭기투는 지난번보다 이번 축하가 더 마음에 든다네요. 선장님은 친구를 잘 고르시는군요 - 여긴 진심이 더 많고, 위선과 가짜 머리카락은 훨씬 적으니까요.";
			link.l1 = "고마워, 친구! 하지만 불술은 마시지 마라 – 여기서는 아주 독하거든.";
			link.l1.go = "Tichingitu_4";
			link.l2 = "고마워, 친구! 한잔 할까? 네가 술을 좋아하지 않는 거 알지만, 오늘만큼은 한번 마셔보는 게 어때!";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "티칭기투는 불물(술)을 좋아하지 않지만, 선장님이 원하신다면 오늘은 마실 수 있소. 당신의 행복과 당신의 여인에게!";
			link.l1 = "그리고 너에게도, 티칭기투! 네 우정과 충성심을 위하여!";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "좋은 파티군, 선장.";
			link.l1 = "만족하셔서 기쁩니다.";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "선장님, 별을 보러 나오셨습니까? 오늘 밤은 아주 아름다울 것 같습니다. 티칭기투는 바다 위의 밤을 사랑합니다. 정말 평화롭지요.";
			link.l1 = "아직 멀쩡히 서 있는 걸 보니 반갑구나, 친구! 네이선과 나는 네 도움이 필요해 – 선술집 녀석들이 술이 다 떨어져서, 조선소 아래 창고에서 술 상자 몇 개를 가져와야 해.";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "앞장서시오, 선장님. 티칭기투는 언제나처럼 당신을 따르겠소.";
			link.l1 = "좋아, 가자!";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "선장님, 사람들이 있습니다, 그리고 무장했어요. 티칭기투가 그들의 무기 소리를 듣고 있는데, 점점 더 크게 들립니다. 마음에 안 들어요. 숨읍시다.";
			link.l1 = "어서 와, 친구야 - 여긴 샤프타운이야. 여기선 화장실 갈 때도 권총 차고 간다니까. 이봐, 네이선... 이런, 젠장! 또 한 병 비웠네. 이러다간 병 다 깨버리겠어! 똑바로 서, 이 자식아! 하하!";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "선장... 너... 티칭기투의 머리가 폭풍 속의 돛대처럼 빙글빙글 돈다. 무슨 일이야?";
			link.l1 = "나도 그걸 물어보려던 참이야! 그동안 어디 있었어?!";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "티칭기투는 이 소녀의 울음소리 때문에 한 시간 전에 깼어. 그 애는 거의 벌거벗은 채로 해변을 뛰어다니면서 납치범이니 야만인이니 뭐니 소리쳤지... 하지만 여기 우리 말고는 아무도 없어. 물 좀 있어? 또 그 불타는 술 말고, 티칭기투는 이제 그거 싫어하거든?";
			link.l1 = "어딘가에 플라스크가 있었는데, 전투 중에 잃어버리지 않았다면... 자, 여기 있다. 어떻게 이걸 해낸 거지? 그녀의 삼촌인 이 동네 바텐더가 조카를 납치한 인디언을 찾고 있는데, 깃털 달린 빈 머리까지 다 찢어버리겠다고 협박하고 있어. 그가 누구를 두고 하는 말이라고 생각해?";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "티칭기투가 기억났어. 그녀는 숲의 악마가 선술집에서 결혼식 준비를 도울 때 같이 있었지. 우리 같이 불술을 마셨고, 티칭기투는 더 마시고 싶어 했어. 그리고 그 스콰... 그녀는 정말 예뻤고... 선장, 나 기억난 것 같아! 티칭기투는 그녀와 결혼하고 싶었어... 카누를 만들어서 그녀를 데려가고 싶었지... 자비로운 영혼들이시여! 아주 나쁜 놈들이 불술을 들고 나타났어. 아마 악마나 사악한 영혼들이었을 거야! 티칭기투는 다시는 ...";
			link.l1 = "그녀를 데려가겠다고? 카누를 만들자고?! 아하, 너 참 낭만적이구나, 친구야... 하하... 하하하하하하 아, 멈출 수가 없어... 웃음이 멈추질 않아!";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "선장님, 티칭기투가 그 여자를 납치해 갔습니다, 맞아요... 그런데, 우리, 음... 이제 결혼 안 해도 될까요? 그 여자는... 앵무새처럼 시끄럽고... 그렇게 예쁘지도 않거든요.";
			link.l1 = "그래, 친구야, 밤새 놀던 여자들은 아침엔 참 처참한 꼴이지. 걱정 마, 영웅 연인아, 우리가 뭔가 생각해낼 테니. 자, 샤프타운으로 돌아가야 해, 네가 휴가 중에 배에 오르는 걸 놓쳤잖아...";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "선상 습격인가? 선장님이 전에 전투를 언급했지. 생각들이 아직 티칭기투의 뜻을 따르지 않아. 마을에서 무슨 일이 있었던 거지?";
			link.l1 = "육지와 바다에서 진짜 전투가 벌어졌지. 대포가 밤새도록 쏘아댔으니, 산호세에서도 들렸을 거야. 하지만 너는 다른 '전투'로 바빴지, 괜찮아, 이해해... 자, 가면서 다 이야기해 줄게.";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "감사합니다, 선장님... 티칭기투는 절대로...";
			link.l1 = "그래, '먼 평원에서 온 종마'라니, 너는 더 이상 마시면 안 되겠다. 가서 좀 자라. 나도 이미 피곤해서 곧 쓰러질 지경이야.";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "선장님, 다시 한 번 축하드립니다! 티칭기투는 지난번보다 이번 축하가 더 마음에 든다 하네요. 선장님은 친구를 잘 고를 줄 아시니, 여기엔 진심이 더 많고, 위선은 적으며, 가발 쓴 자들도 드물지요.";
			link.l1 = "그리고 불물도 훨씬 더 많지. 그런데, 나랑 한잔 할래? 네가 술을 안 좋아하는 거 아는데, 오늘은 특별한 날이잖아!";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "티칭기투는 불물(술)을 좋아하지 않지만, 선장님이 원하신다면 오늘은 마시겠소. 당신의 행복과 당신의 여자에게! 두 분이 같은 길을 걷기를, 그리고 해와 달이 언제나 그 길을 비추기를 바라오.";
			link.l1 = "고마워, 친구야. 티칭기투, 네게 건배! 우리의 우정을 위하여!";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "대단한... 축하야, 정말 기쁘구나, Charles. 하지만 아직도 네가 이해가 안 돼... 값을 매길 수 없는 장미를 손에 쥐고도... 들꽃과 바꾸다니. 그래도 마음이 원하는 대로 가는 거겠지... 행복해라, 친구야. 오래오래 행복하게 살아라!";
				link.l1 = "그대가 쥔 꽃에서 가장 아름다운 것은 그 꽃을 향한 그대의 마음이오. 그 마음이 없다면, 그저 시들어가는 살덩어리일 뿐이오. 와 주셔서 기쁩니다, 나리.";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "멋진 날이네, 친구, 그리고 멋진 일이야! 진심으로 축하해! 나는 세 번이나 결혼했는데, 매번 처음인 것처럼 떨렸지, 아, 젊은 시절이여...";
				link.l1 = "나리, 아직 늙으려면 멀었으니 기죽지 마시오. 와줘서 고맙네, 자크!";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "잠깐, Charles. 네가 오해했구나, 나는 진심으로 정말 기쁘다! 그리고... 자, 받아라. 우리 둘의... 친구가 오늘 네가 꼭 이것을 받으라고 특별히 부탁했어.";
			link.l1 = "누가 보낸 건지 짐작이 가는군. 고맙네, 곧 다시 보자고.";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "정말 멋진 의식이군, Charles? 진심으로 축하하네! 나와 바스테르 시민 모두를 대표해 자네와... 매력적인 부인께 축하를 전하네. 두 분 참 잘 어울리는 한 쌍이야! 오래오래 행복하게 사시게!";
			link.l1 = "감사합니다, 각하. 마음에 드셨다니 기쁩니다.";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "이렇게 훌륭한 대접을 받다니, 드 마우르 나리, 정말 훌륭하군요! 그리고 신부는 이 복장으로 정말... 독특하십니다. 우리 도시 모든 주민을 대표해서 진심으로 축하드립니다! 앞으로도 행복한 세월이 가득하길 바랍니다!";
			link.l1 = "감사합니다, 각하.";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "정말 매력적이었어요 – 당신과 신부님, 드 모르 나리, 두 분이 참 독특해 보였어요! 하지만 당신은 정말 특별한 분이십니다. 오래오래 행복한 결혼 생활 하시길 바랍니다. 두 분이 영원히 행복하게 사시길!";
			link.l1 = "대단히 감사드립니다, 각하.";
			link.l1.go = "Guests_block";
		break;
		
		// д'Ойли
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "그대의 결혼을 위해 카리브를 건넌 보람이 있었소! 모든 영국 식민지 주민들을 대표하여 축하드리오, 선장님! 그대와 신부—아니, 이제는 아내지—두 분은 정말 잘 어울리는 한 쌍이오!";
			link.l1 = "방문해 주시고 친절한 말씀을 해주셔서 감사합니다, 대령님!";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "그리고 이 유부남 멋쟁이가 내 해적 해변에서 뭘 하고 있는 거지, 응?! 말해 봐라, 나리, 내 오랜 친구이자 거친 해적 찰리 프린스는 어떻게 된 거냐?";
					link.l1 = "찰리 프린스는 죽었지, 기억하지 마커스... 하하하, 이리 와라, 이 바다의 악마야! 널 다시 보게 되어 반갑다! 여기 어때, 다들 모였나?";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "이 결혼한 멋쟁이가 내 해적 해변에서 뭘 하고 있는 거지, 응?! 말해 봐라, 나리, 내 오랜 친구이자 거친 선장인 샤를 드 모르에게 무슨 짓을 한 거냐?";
					link.l1 = "아, 마커스, 나도 너를 보게 되어 반갑다! 여기 모두 잘 지내고 있나, 다들 모였어?";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "그리고 이 유부남 멋쟁이가 내 해적 해변에서 뭘 하고 있는 거지, 응?! 말해 봐라, 나리, 내 오랜 친구이자 거친 선장인 샤를 드 모르를 어떻게 한 거냐?";
				link.l1 = "아, Marcus, 나도 너를 보게 되어 반갑다! 여기 모두 잘 지내고 있나, 다들 모였어?";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "그래, 숲의 악마가 바로 어제 도착하더니 곧장 명령을 내리기 시작했어 – 그래서 손님들도 와 있고, 축제 준비도 다 끝났지. 네 배가 암초 근처에서 목격됐고, 녀석들이 참지 못하고 선술집으로 달려가서는 아마 이미 그 호크의 술통을 열었을 거야. 서둘러, 우리도 한 잔 나눌 기회가 아직 있을지 몰라 – 네이선리얼이 이번 럼은 뭔가 특별하다고 자랑했거든!";
			link.l1 = "이게 바로 우리가 노는 방식이지 - 배에서 바로 파티로 가는 거야! 내 반쪽 기다렸다가 바로 따라갈게, 마커스!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "그래, 숲의 악마가 바로 어제 도착하자마자 명령을 내리기 시작했어. 그래서 손님들도 와 있고, 축제 준비도 다 끝났지. 네 배가 암초 근처에서 목격됐고, 녀석들이 참지 못하고 선술집으로 달려가서 아마 벌써 그 호크의 술통을 땄을 거야. 서둘러, 어쩌면 아직 한 잔 할 기회가 남았을지도 몰라. 네이선리얼이 이번 럼은 뭔가 특별하다고 자랑했거든!";
			link.l1 = "이게 바로 우리가 노는 방식이지 - 배에서 바로 파티로 가는 거야! 내 짝 기다렸다가 곧 따라갈게, Marcus!";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "샤를 드 모르와 결혼했다니... 아직도 익숙하지가 않아. 처음엔 스벤손, 이제는 너라니—그 다음은 뭐지? 말로 신부, 아니면 친절한 자크인가?";
			link.l1 = "너는 호크스에 대해 잊었군. 그리고 너는 어때, 마커스? 혼자 바다를 떠도는 늑대 노릇, 이제 지겹지 않아?";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "대니와 네이선은 오래된 일이지 - 난 이미 받아들였어. 하지만 너는 정말 나를 놀라게 했구나! 그런데 숲의 악마 제자란 여자는 정말 미인이야 - 진짜로, 말도 잘하고 권총도 늘 준비되어 있지, 어떤 폭풍도 견딜 수 있는 여자야. 너보다 더 어울리는 여자를 찾기 힘들 거다. 운 좋은 놈이야, 선장 - 그녀 잘 챙겨!";
			}
			else
			{
				dialog.text = "대니와 네이선은 오래된 일이야 – 나는 이미 받아들였지. 하지만 너는 정말 나를 놀라게 했어! 듣자하니 네 메리는 검에 대해 잘 알고, 그걸 다룰 줄도 안다면서? 존경을 표하지. 진정한 전우로군. 비밀 하나 말해주지, 그런 아가씨라면 나도 총각 신념을 다시 생각해볼지도 모르겠어. 운 좋은 사람이야, 선장 – 그녀를 잘 챙기라고!";
			}
			link.l1 = "알아, 그녀는 정말 기적이야. 난 다시 한 번 행복해서 하늘을 나는 기분이야 - 우리가 처음 만났던 그 시절처럼!";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "자, 건배하자!... 사랑을 위하여!... 하지만 우리를 문턱 너머, 지평선 너머로 내모는 사랑이 아니라!… 바로 이 문턱에서 우리를 기다리는 사랑을 위하여! 세상 끝과 황금산에서도 우리를 다시 불러들이는 그 사랑을 위하여! 그 사랑과 함께 살고, 행복하라!";
			link.l1 = "멋진 건배였어, Marcus, 고마워!";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "건배, 네 결혼을 위해, 친구!";
			link.l1 = "고맙소, Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "자크? 이거 정말 안 좋은데...";
			link.l1 = "마커스, 너 생각에는...";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "시간이 없어! 놈들이 문 뒤에 있어! 모두 무장해!";
			link.l1 = "자, 간다!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "내가 이렇게 파티에서 신나게 논 게 언제였는지 기억도 안 나! 아직 끝난 거 아니야! 들리냐? 밖에서 누가 총 쏘고 있어! 놈들의 피로 거리를 물들여 주자!";
			link.l1 = "잠깐! 저놈들은 대체 뭐야!? 그리고 도대체 뭘 원하는 거지!?";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "결혼한 드 모르 선장, 이렇게 진심으로 건배할 이유를 만난 적은 드물었소. 잔을 들어! 이건 평범한 양배추 술이 아니오. 동인도산 홍차와 진짜 페르시아 향신료가 들어갔으니!";
			link.l1 = "그래서 목이 타는 것처럼 뜨거운 납을 마신 기분이 드는 이유가 뭔지 궁금했지. 뭐, 네이선, 건배...";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "잠깐, 먼저 건배부터 하자! 이봐, 신사 여러분, 잔을 들어라! 오늘은 우리 친구이자 동료인 샤를 드 모르가 가정의 길로 나서는 날이야. 우리 모두의 깊은 애도... 아, 대니, 제발 총 좀 내려놔! 물론 축하한다! 이제 너희는 한 배의 돛이니, 어떤 폭풍도 함께 헤쳐서 가장 풍요로운 해안까지 이끌어 가라!\n";
			link.l1 = "진심으로 감사하네, Nathan. 너와 Danielle은 우리가 본받아야 할 본보기야.";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "좋은 소식이군. 내 아내와 나는 세상에서 가장 좋은 부부는 아닐지 몰라도 함께 행복하게 살고 있네. 그리고 자네가 우리를 위해 정말 많은 일을 해줬으니, 내 생각엔 자네는 내 가족이나 다름없어. 언제든 도움이 필요하면 내가 여기 있을 걸세. 행복하게 지내고, 한잔 하게나!";
			link.l1 = "그럼 마시자! 오... 이 럼은 성스러운 종교재판소의 무기고에 있어야 할 술이야. 젠장! 목구멍을 타고 내려가면서 다 태워버리네... 악! 휴우!... 맘에 드는군!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "너, 20년 전의 나랑 대니랑 정말 똑같이 생겼구나!";
			link.l1 = "한 잔 더 줘, Nathan!";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "뭐라고!? 얀 녀석이 너를 지하 저장고로 와인 가지러 보냈다고? 같이 가자, 내가 도와줄게. 바람도 쐬면 우리한테 좋을 거야.";
			link.l1 = "하지만 Dannie와 "+sld.name+"? 얀은 그들이 이야기를 하러 갔다고 내게 말했어.";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "그래, 대니도 아무리 훌륭한 여전사가 있어도 운 좋은 신사들이 완전히 쉴 수는 없다는 걸 알고 있지. 그래서 그녀들은 받은 칭찬을 다 듣고는 남자들이 실컷 즐기도록 저택으로 들어갔어.";
			link.l1 = "자, 그럼 가자! 맥주 몇 잔은 마셨지만, 젠장, 이제야 제대로 취할 시간이네!";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "자, 여기 상자가 있군. 들 수 있는 만큼 챙기고 나서 돌아가자, 이 늙은 잔소리꾼이 우리를 여기 가둬버리기 전에.";
			link.l1 = "너무 과장하지 마, 네이선. 그 녀석 그렇게 나쁘진 않아... 잠깐, 방금 들었어?";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "얀이 아마 더 많은 놈들을 찾아서 우리를 도우라고 보냈겠지. 젠장!";
			link.l1 = "어서, 병을 깨뜨려야 행운이 온다. 하나 더 마시고 가자.";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "대체 무슨 일이야, 저 놈들은 누구지? 이게 뭔지 알겠어, Charles?";
			link.l1 = "나도 모르겠어, Nathan, 하지만 그들 중 한 명이 도움을 청하러 달아났고, 더 많은 발소리가 들리는 것 같아. 우리 술집으로 돌아가야 해!";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "이 자식들은 해치웠지만, 바다에서 대포 소리가 울려 퍼지는 거 안 들려? 지금 전투 준비된 선원은 두 척뿐이야, 마커스의 프리깃하고 얀의 코르벳. 나랑 대니, 그리고 다른 녀석들은 사람들 다 상륙시켰어. 결혼식이니까 말이지. 그래서 센츄리온은 빠졌어. 네 배는 어때? 어떻게 할지 빨리 결정해야 해!";
			link.l1 = "선원 절반은 상륙시켰고, 나머지는 제정신이길 바란다. \n하지만 먼저 아내를 찾아서 무사한지 확인해야 해.";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "그래, 대니도 어디에도 안 보여. 그럼 이렇게 하자 - 타이렉스랑 스벤슨은 이미 항구로 달려갔으니, 곧 배에 도착할 거야. 우리는 아내들을 위해 관저로 간다. 나머지는 해안에서 방어를 준비해야 해. 네 장교 몇 명을 네 배로 보내서 사람들을 모으게 할 수 있겠어? 거기서 도와주는 게 분명히 도움이 될 거야.";
			link.l1 = "좋아, 모두들, 움직이자! 매 순간이 중요하니까!";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "더 빨리, 위층으로! 대니랑\n "+sld.name+" 반드시 거기 있어야 해! 그리고 저 놈들이 그들을 다치게 했다면...";
			link.l1 = "꿈도 꾸지 마! 위층으로! 가자!";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "젠장! 네 친구가 그 자식이 여자애들을 쏘지 못하게 하려고 총구 앞으로 곧장 달려들었어!";
			link.l1 = "그리고 그는 총에 맞았어... 잠깐만, 네이선... 숨 쉬고 있어! 아직 살아 있어! 젠장, 지노가 필요해! "+sld.name+", 자기야, 잘 지냈어?";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "우린 괜찮아, Charles! 내가 그녀를 풀어줄게. 항구에서 총소리가 들려 – 너랑 Nathan은 거기로 가야 해, 안 그러면 Barbazon이 우리 배를 전부 박살낼 거야. 시간 낭비하지 마!";
			link.l1 = "내가 지노를 찾아서 여기로 보내겠어, 그가 도와줄 거야... 반드시 그래야 해! "+sld.name+", 자기야, 여기 있어, 둘 다 저 사람을 돌봐.";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "찰스, 서둘러! 어떻게 결정하든 지금은 시간이 금보다 더 귀해! 자크의 배들이 해안까지 돌파하면 모든 게 헛수고가 되고 말 거야!";
			link.l1 = "그래, 알아. 젠장할 놈!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "더 빨리 가! 얘기할 시간 없어!";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "젠장! 미안해, Charles. 우리가 위층에 갇혀 있었어, 저 망할 놈들이 열두 명이나 있었거든... 내가 제때 도착하지 못한 게 아쉽지만, 네가 상황을 아주 잘 해결한 것 같네.";
			link.l1 = "쉽진 않았지만, 젠장, 그 '착한 놈'을 죽이는 데 엄청난 쾌감을 느꼈지! 이제 상륙할 시간이야, 네이선. 우리 사람들이 거기서 기다리고 있어!";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "그래, 네 인디언 소년을 만나러 가야 해. 여기서 일 마치고 샤프타운으로 가자.";
			link.l1 = "네 말이 맞아, 내가 바로 뒤에 있어.";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "그런데 말이야, 마커스를 찾았어! 그는 화물창에 묶인 채로 의식을 잃고 있었어.";
			link.l1 = "살아 있어?";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "상태가 좀 안 좋긴 하지만 괜찮을 거야. 타이렉스는 웬만한 놈보다 훨씬 강하니까 걱정 마. 이미 네 배로 옮겨졌고, 벌써부터 세이버를 달라고 하더라.";
			link.l1 = "드디어 좋은 소식이군! 좋아, 여기서 마무리하고 돌아가자.";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = "안녕, Charles. 좀 보자꾸나 – 더 잘생겨졌구나, 불평할 게 없네! 거의 10년 전의 Nathan 같아! 어서 들어와, 문간에 서 있지 말고, 모두가 널 기다리고 있었어!\n";
			link.l1 = "고마워, Dannie, 정말 반가워! 나중에 너랑 Nathan한테 갈게, 그때 이야기하자!";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "Charles, 자리에 앉아. Nathan이랑 나는 네가 정말 기뻐! Marcus, Jan 그리고 내 남편이 너를 위해 뭔가를 준비했어 - 하지만 선물은 나중이야. 우선, 축하하고 행복을 빌어줄게! 네 사랑은 정말 대단한 사람이야! 그런데 말이야, Martinique에서 그녀에게 흰 드레스 입히는 데 성공하지는 못했지?";
			link.l1 = "고마워, 대니. 그래, 그 드레스 사건은 꽤 웃겼지 – 우리 결혼식이 상류 사회에서 온갖 스캔들 소문을 불러일으켰을 거라고 확신해. 모두가 예의상 못 본 척, 아무 일도 없는 척했지. 예의라는 게 다 그렇지 뭐 – 하지만 나는 소문 따위 신경 안 써. 내가 그녀를 사랑한다는 게 가장 중요한 거니까.";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "네 말이 완전히 맞아! 나도 허리에 칼과 권총 두 자루를 차고 제단까지 걸어갔지. 하지만 그건 포트 로얄에서였어, 그곳이 아직 제대로 된 식민지 거주지가 되기 전이었지. 그 시절엔 정말 재미가 넘쳤어, 르바쇠르가 있던 토르투가보다도 더 말이야, 아무도 놀라지 않았고... 에휴. 그런데 내가 계속 수다만 떨고 있네 - 손님들 좀 둘러봐, 모두 여기서 널 기다리고 있었으니, 와서 한 번 안아 줘!\n";
			link.l1 = "아, 대니, 내가 어찌 너를 거절할 수 있겠냐, 하하! 내 아내랑 나는 너희 모두를 보게 되어 얼마나 기쁜지 상상도 못할 거야!";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "찰스, 너희 둘 정말 잘 어울린다!";
			link.l1 = "고마워, Dannie...";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "샤를, 저 사람 말이 맞아... 너한텐 선택지가 없어. 자크 더 카인드맨이 타이렉스랑 그 일당을 다룬다면 자비 따윈 없을 거야. 뭘 해야 하는지 알잖아.";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "저 자식 말 듣지 마! Kingman이 그런 미친 짓을 하기로 마음먹었다면, 누구도 가만두지 않을 거야!";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "우린 괜찮아, Charles! 내가 그녀를 풀어줄게. 항구에서 대포 소리가 들려, 너랑 Nathan은 거기로 가야 해, 안 그러면 Barbazon이 우리 배를 통에 든 오리처럼 가라앉힐 거야. 한순간도 허비하면 안 돼!";
			link.l1 = "내가 지노를 찾아서 여기로 보내겠어, 그가 도와줄 거야... 아니, 반드시 도와야 해, 젠장! "+sld.name+", 자기야, 여기 남아서 티칭기투를 돌봐 줘.";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "네이선, 안 돼!!!";
			link.l1 = "그는 그 순간을 포착해 대포로 달려가서 너를 엄호했어, 대니... "+sld.name+", 자기야, 잘 지냈어?";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "그래, Charles, 그 사람 살아 있어! 심장이 겨우 뛰고 있지만, 살아 있단 말이야! 어떻게 해야 하지?!";
			link.l1 = "지노가 당장 필요해! 내가 그를 찾아서 여기로 보내겠어, 그가 도와줄 거야... 반드시!";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "찰스, 우리에겐 시간이 없어! 자크의 배들이 해안까지 뚫고 들어오면 모든 게 허사가 돼! 내 남편은... 해야 할 일을 했어. 이제 네 차례야. 나는 그와 함께 남을게. 너희 둘은 가서 지노를 찾아!";
			link.l1 = "그래, 나도 알아. 피투성이 개자식, 반드시 대가를 치르게 해 주지!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "드디어 왔군! 모두 무사한가?";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "우린 괜찮아, 대니. 걱정하지 마. 자크는 죽었고, 그의 배들은 바다 밑에 가라앉았어. 티칭기투는 어때?";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "우린 괜찮아, 대니. 걱정하지 마. 자크는 죽었고, 그의 배들은 바다 밑에 있어. 네이선은 어때?";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "괜찮아! 네 이탈리아인 의사는 천재야! 네이선은 위층에서 자고 있는데, 지노 말로는 아무 문제도 없대. 침대에서 일주일이나 이주일 정도 쉬고, 레드 와인, 그리고 지노가 말하길 '그에게 호의적인 숙녀의 방문'이 필요하다더군... 에헴... 아무튼, 다 괜찮아. 또 한 번 우리를 구해줬어, Charles, 어떻게 감사해야 할까?";
				link.l1 = "내 아내와 자네를 구한 건 네이선리얼이었어. 이 은혜는 평생 갚아야지. 그가 회복 중이라는 소식을 들으니 얼마나 기쁜지 자네는 상상도 못 할 거야. 그를 쉬게 해 주게, 나중에 다시 와서 자네들을 살펴보겠네.";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "괜찮아, 총알이 관통해서 지나갔고, 우리 'Centurion'에서 온 외과의가 멀지 않은 곳에 있었어. 이 난리통을 피해 숨어 있었지. 그러니 네이선은 살 거야, 침대에 몇 주만 누워 있으면 돼 – 별일 아니야!";
				link.l1 = "대니, 그는 내 아내와 너를 총알로부터 지켜줬어. 난 평생 그 은혜를 갚아야 해. 그가 회복 중이라는 소식을 들으니 얼마나 기쁜지 상상도 못할 거야. 그를 쉬게 해 줘. 나중에 다시 와서 너희를 살필게.";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "물론이죠! 하지만 이제 가봐야 해요, 남편에게 가야 하거든요... 친구분을 잠시 빌려도 괜찮을까요? 네이선이 회복되면 제가 직접 그를 앤티가로 데려가겠어요. 센츄리온은 어떻게든 기적적으로 살아남았고, 이제 새 선원만 모집하면 돼요.";
			link.l1 = "좋아, 대니, 지노랑 네이선에게 안부 전해 줘. 난 이제 가봐야겠어.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "물론이지, Charles, 하지만... 나쁜 소식이 있어. 네 결혼식에 왔던 그 이탈리아인, Guineili 말이야... 그의 시신이 선술집 방에서 발견됐어. 나... 미안해, Charles.";
			link.l1 = "뭐라고? 지노?! 안 돼! 어떻게 된 거야?";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "나도 몰라, 아마 지하묘지를 통과해서 마을을 공격한 그 놈들 중 하나겠지. 분명 거기 숨어 있다가 도망칠 기회를 노리고 있었고, 그를 발견한 거야...";
			link.l1 = "젠장! 아니, 믿을 수가 없어...";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "미안하네, Charles. 정말 피비린내 나는 학살이었고, 그는 싸움꾼이 아니었어... 원하신다면 그의 시신을 당신 배로 보내드리겠소, 집으로 데려가 제대로 장례를 치를 수 있게 말이오. 진심으로 유감이오...";
			link.l1 = "고맙다, Dannie. 시신을 배에 실으라고 명령을 내려라. 이제 가봐야겠다... 생각할 시간이 필요해. 그리고 Nathan에게 안부 전해줘.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "괜찮아! 네 이탈리아 의사는 천재야! 그는 위층 방에서 자고 있고, 지노가 돌보고 있어. 지노 말로는 '일주일이나 이주일이면 괜찮아질 거라'더라.";
				link.l1 = "좋은 소식이군! 아직 그를 바로 만나러 갈 수는 없는 건가?";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "정말 미안해, Charles. 센튜리온에서 우리 외과의를 찾아왔지만, 아무것도 할 수 없었어... 네 친구는 몇 시간 전에 죽었어.";
				link.l1 = "티칭이투?! 아니! 믿을 수 없어!!!";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "아니, 그 이탈리아인은 절대 그를 방해하지 말고 쉬게 하라고 엄하게 금했어. 그리고 지노도 그동안의 걱정 끝에 좀 쉬어야지. 나도 말했어\n "+sld.name+" 모든 게 괜찮아질 거란 걸 알게 됐을 때 산책하러 나갔었지\n그리고 한 가지 더... 네 친구가 총알을 막아줬어. 어떻게 고마움을 전해야 할지 모르겠구나. 앞으로는 그도 우리 가족이나 다름없다고 꼭 전해줘. 그리고 너, 또 한 번 우리를 구했구나, Charles!";
			link.l1 = "끝이 좋으면 다 좋은 거야, 대니. 네이선에게 가, 그가 널 기다리고 있었으니. 나는 여기서 잠깐 쉬면서 내 \n "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "미안해, 내가 할 수 있는 건 다 했어, 그리고 "+sld.name+", 역시. 그가 우리를 그 총알로부터 지켜줬어, 그리고 나는 절대 잊지 않을 거야, 믿어줘.";
			link.l1 = "... 오래전에 그는 나를 위해 죽을 수 있다고 말했었지... 아마 자신이 우리 모두를 위해 목숨을 바치게 될 줄은 몰랐을 거야... 이제 그는 영웅이 되었고, 나는 그를 영원히 그렇게 기억할 거야... 어디 있지 "+sld.name+"? 그녀는 괜찮아?";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "그렇게 말할 수는 없어... 그러니까, 신체적으로는 맞아. 하지만... 알잖아... 그녀가 산책 나가서 머리를 식히고 오겠다고 했어. 아마 네가 정박한 걸 보고 곧 돌아올 거야.";
			link.l1 = "빌어먹을 자크 바르바종... 진작에 저놈을 죽였어야 했는데!";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "잠깐만... 아직 끝난 게 아니야. 그 이탈리아 놈, 귀네일리 말이지? 그 조용한 청년. 그가... 그의 시체가 선술집에서 발견됐어... 잘은 모르겠지만, 아마도 지하묘지를 통과해서 마을을 습격한 그 놈들 중 하나였겠지. 분명히 거기 숨어 있다가 도망칠 기회를 노렸고, 그를 발견한 거야...\n";
			link.l1 = "지노까지?! 오늘은 정말 재수 없는 날이구나...";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "미안하오, Charles... 원하신다면 시신을 당신 배로 보내고, 부하들을 집으로 데려가 그들이 마땅히 받아야 할 장례를 치르게 하겠소. 진심으로 유감이오...";
			link.l1 = "고맙다, 대니. 해... 난 가봐야겠어... 생각이... 필요해.";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "찰스, 네 결혼 때문에 얼마나 많은 여자애들 마음이 부서졌는지 상상이나 해 봤어? 그래, 군도에 있는 여자애들 절반은 네 결혼식 끝나고 슬퍼했을 거다, 하하!";
			link.l1 = "어쩔 수 없지 - 난 한 명만 필요했고, 그 애를 얻었으니까. 하지만 아직 여자애들이 속상해할 때는 아니야, 왜냐면 아직도 너, 스티븐이 있으니까.";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "그거야 사실이지! 여기 일 끝내고 바로 놈들 처리해 줄게, 젠장! 자, 찰스, 네 운과 가정에 건배하자. 그러니까, 흔히들 말하듯이, 오래오래 행복하게 살아라!";
			link.l1 = "고마워, 친구!";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "행복한 가정생활을 위하여, 하하!";
			link.l1 = "건배!";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "찰스, 너 이번 결혼으로 얼마나 많은 여자애들 마음을 아프게 했는지 상상이나 해 봤어? 그래, 군도에 있는 여자애들 절반은 네 결혼식 끝나고 울었을 거다, 하하!";
			link.l1 = "어쩌겠어 - 난 한 명만 필요했고, 그 애를 얻었지. 하지만 아직 여자애들이 속상해할 때는 아니야, 왜냐면 아직 너, 베르나르가 있으니까.";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "그래, 맞는 말이지! 여기 일 끝내고 바로 저놈들 처리해주마, 젠장! 자, 찰스, 네 행운과 가정에 건배하자. 그러니, 흔히들 말하듯이, 오래오래 행복하게 살아라!";
			link.l1 = "영원히 행복하게 살았지!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "행복한 가정생활을 위하여, 하하!";
			link.l1 = "훌륭한 건배다!";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "하, Charles, 너도 이제 결혼해서 재미없는 놈이 됐구나, 우리 옛날 Nathan처럼! 그 난잡한 연애질도 다 옛날일이지, 응? 이제 제대로 된 가장이네!";
			link.l1 = "기다려, 베르나르! 내 아내는 집안 폐허 창가에 앉아 따분해할 여자가 아니야! 달라질 건 여기서부터 퀴라소까지 창녀들 지갑이 더 두둑해질 뿐이지!";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "큰 손해는 아니라고 본다! 닉켈 동전 한 자루보다 금화 한 닢이 낫지. 한잔하자! 자네와 자네 아내를 위해 건배! 금은 잘 챙기고 행복하게 살아!";
			link.l1 = "고마워, Bernard. 오, 이거 정말 독한 럼이네. 휴!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "네 신부, 아니, 이제는 네 아내에게!";
			link.l1 = "감사합니다!";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "딱 맞춰 왔군, Charles, 고맙다!";
			link.l1 = "여기서 뭐가 재밌다고? 난 너희가 이미 항구에서 배에 짐 싣고 있는 줄 알았는데.";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "마커스가 나를 해안 방어를 맡기고 떠났어. 인원이 부족하고, 항구에 있는 녀석들은 화약이 필요해. 그래서 잠깐 들러서 통 몇 개 챙기려고 했지... 그런데 이 깡패들이 나타난 거야. 하, 숨어 있다가 상황을 보거나 누굴 털려고 했던 모양이지. 그리고 나는 아직도 호크의 럼주가 잔뜩 들어 있어서, 네가 아니었으면 지금쯤 살아 있을지 모르겠어.";
			link.l1 = "언제든 환영이야. 좋아, Bernard, 네가 마을 안전을 책임져. 나는 가야겠어. 몸조심해!";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "선장님, 이 경사스러운 날에 진심으로 축하드립니다. 사랑하는 분과 함께 행복하시고 서로 아끼며 살아가시길 바랍니다!";
			link.l1 = "고마워, 지노. 와 주기로 해서 기쁘다! 이곳의... 분위기가 불편하지 않았으면 좋겠는데?";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "이건... 정말 배울 게 많은 여행이야. 솔직히 말해서, 나는 오랫동안 앤티과를 떠난 적이 없었고, 이 사회에서는 쉽게 편해지기가 어렵지. 하지만 넌 항상 사람을 잘 이해했으니, 나도 네가 있어서 믿고 최대한 침착하게 있으려고 해.";
			link.l1 = "좀 더 독한 술이 필요한 거 아냐?\n긴장 풀고 누군가랑 얘기나 해봐.";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = ""고맙소, 선장. 물 탄 포도주는 이제 충분하오. 술은 간에도, 어쩌면 심장에도 별로 좋지 않다는 점을 미리 경고하겠소. 대화라면, 저기 있는 신사와 치릭-사난고의 치유 효능에 대해 이야기해 보려 했소. 마나카라고도 불리는 그것 말이오. 메인 원주민들이 그것을 사용하는데..."\n";
			link.l1 = "짐작컨대, 저 신사는 대화에 끼지 못했나 보군? 지노, 내 부탁이니 오늘만큼은 저기 카운터에서 얀이 따라주는 럼을 한번 마셔봐. 그 안에 들어간 재료를 전부 맞출 수 있다면, 저기 있는 네이선 호크가 아주 감탄할 거야. 분명 그도 네가 함께해주면 기뻐할 테고, 카운터에 있는 스벤손도 마찬가지일 거야. 둘 다 교양 있는 사람을 존중하거든.";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "자네의 건강을 위해, 그리고 자네의 매력적인 배우자의 건강을 위해!";
			link.l1 = "고맙다, 친구!";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "선장님, 당신이군요, 신께 감사드립니다! 그 가면 쓴 자들, 내가 봤고 여기 숨어 있었어요, 그놈들이 문을 부수려고 했어요...";
			link.l1 = "괜찮아, Gino, 이제 아무도 너를 해치지 않을 거야. 내가 널 찾아서 정말 다행이야, 네 도움이 필요해. 내 친구가 다쳤어 - 총에 맞아서 피를 많이 흘렸어. 서둘러야 해!";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "총알... 피... 전 괜찮아요, 선장님. 여기 오는 길에 혹시 다칠까 봐 의료 상자랑 도구들 다 챙겨 왔어요. 그 사람한테 데려가 주세요, 뭘 할 수 있을지 볼게요. 그리고 저... 가면 쓴 놈들, 혹시 다른 데 숨어 있는 거 아닐까요?";
			link.l1 = "분명히 그들이 마지막이었어. 지노, 항구에서 전투가 벌어지고 있어서 내가 지금 바로 가야 해. 너는 혼자서 관저로 가야 해, 멀지 않아. 큰 집이 모퉁이 돌아서 바로 있으니 절대 못 놓칠 거야. 겁내지 마, 거리에 우리 사람들이 가득하니까. 그리고 서둘러, 제발 부탁이야!\n";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "선장님, 이 경사스러운 날에 진심으로 선장님과 사랑하는 분께 축하를 드립니다!\n행복하시고 서로를 잘 돌보시길 바랍니다.";
			link.l1 = "고마워, Gino. 와 주기로 결정해서 기쁘다! 오는 길은 순조로웠나?";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "모든 게 괜찮습니다, 선장님, 걱정해 주셔서 감사합니다. 한 가지 말씀드리자면 - 저는 오랫동안 앤티과를 떠난 적이 없어서, 이런 상류층 사람들 사이에서는... 그다지 편하지가 않습니다. 하지만 이번에 온 이유가 달리 선택의 여지를 주지 않았지요. 그런데 서비스가 훌륭해서, 두 분 모두 정말 기쁩니다! 신부가 이 옷을 입으니 참 매력적이군요 - 이게 새로운 유행인가요? 제가 세상 흐름에 뒤처진 것 같지만, 정말 마음에 듭니다.";
			link.l1 = "유행... 뭐, 어떻게 보면 그렇지, 아니면 곧 그렇게 될 거야. 좋아, 잘 놀아, 지노. 그리고 귀족들이 지루해지면 항구로 와. 선원 전부가 선술집에 있어. 녀석들이 널 보면 분명 좋아할 거야.";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "선장님, 다시 한 번 축하드립니다. 그리고 아름다운 부인께도요! 두 분이 오래오래 행복하시길 바랍니다!";
			link.l1 = "고마워, 지노. 와줘서 기쁘다! 이곳의... 분위기가 거슬리지 않길 바란다?";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "이 사회에서는 내가 편하게 느끼기 쉽지 않아. 하지만 너는 항상 사람을 잘 골랐으니, 나는 네가 믿는 만큼 침착하게 있으려고 해.";
			link.l1 = "좀 더 독한 술이 필요한 거 아냐?\n긴장 풀고 누군가랑 얘기나 해봐.";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "감사합니다, 선장님, 이제 물 탄 와인은 충분히 마셨습니다. 알코올은 간이나 어쩌면 심장에도 별로 좋지 않다는 점을 경고해야겠군요. 대화라면, 저 신사분과 치릭-사난고의 치유 효능에 대해 이야기해 보려 했습니다. 마나카라고도 불리죠. 메인 원주민들은 그것을...";
			link.l1 = "내가 맞춰볼까? 저 신사는 대화를 감당하지 못했나 보군. 지노, 오늘만 나를 위해서라도 저기 카운터에서 얀이 따라주는 럼을 한번 마셔봐. 그 안에 들어간 재료를 전부 맞출 수 있다면, 저기 있는 네이선 호크가 아주 감탄할 거야. 네가 곁에 있으면 분명히 기뻐할 거고, 카운터에 있는 스벤손도 마찬가지일 거야. 둘 다 식견 있는 사람을 존중하거든.";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "'이국땅에 홀로 남아, 이방인인 듯한 기분으로, 이렇게 밝은 축제날에 더욱더 내 가족이 그리워진다'";
			link.l1 = "Longway, 네가 말재주가 그렇게 뛰어난 줄은 몰랐어!";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "미안합니다, 선장님. 요즘 생각이 많았습니다. 이 말은 왕유라는 시인의 말인데, 그는 오래전 제 고향을 다스렸던 당나라 시대에 살았던 사람입니다.";
			link.l1 = "이 말들은 정말 아름답구나. 언젠가 네가 다시 고향을 볼 수 있기를 바란다...";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "''신비로운 돌판 아치 아래를 지나가려 해도, 그 너머에 우림 계곡이 있다는 걸 보증하거나 알 수 없다는 게 정말인가?\n아니요, 선장님, 당신도 알다시피 롱웨이는 집으로 돌아갈 생각이 없소. 이제 여기가 내 집이고, 오늘 이곳에서 큰 행사가 있소! 당신과 아름다운 신부께 최고의 축복을 보냅니다! 두 분의 행복이 양쯔강처럼 길고, 연꽃의 진주 사이로 별의 다이아몬드가 박힌 것처럼 빛나길 바라오.''";
			link.l1 = "고맙네, 내 오랜 친구. 자네의 말은 왕웨이의 시만큼이나 아름답구먼.";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "한잔 합시다, 선장님! 이 럼은 슬픔을 날려버리고 기쁨을 되살려주니, 마오타이 못지않게 좋습니다.";
			link.l1 = "네 건강을 위하여, Longway!";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "멋진 결혼식이었어요, 선장님!";
			link.l1 = "마시고 신나게 놀아라!";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "쇄탄을 쏴라! 우리 모두가 너를 축하한다! 발사는 어땠어?";
				link.l1 = "다 잘됐어, 찰리! 이제 나는 공식적으로 결혼했고 체면도 세웠지. 그리고 내 일등항해사는 이제 몽페르 부인이야.";
			}
			else
			{
				dialog.text = "체인 샷으로 한 방 맞은 기분이군, 대단한 일이야, 선장! 브라더후드의 거의 모든 남작들이 다 모였어! 아마 스페인 청교도 놈들은 지옥이 딱 이런 곳이라고 생각하겠지! 그리고 이 럼주, 정말 특별해, 내 술통에 체인 샷 한 방 맞은 것 같아!";
				link.l1 = "그래, 여기 사람들은 법을 잘 지키는 편은 아니지만, 우리도 천사는 아니잖아, 찰리. 그리고 이들 모두가 나에게는 저마다 소중한 사람들이야.";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "끝내주네, 내 엉덩이에 쇄탄이나 맞은 기분이야! 선장님, 그러니까, 이 축하연은 선장님을 위한 거요, 저기, 나는... 축하드린다고, 그러니까... 또... 행복과... 저기, 나는 말솜씨가 별로라서. 하지만 한 가지는 꼭 알아두시오, 우리 모두 선장님 두 분을 정말 사랑하고, 지옥까지라도 따라갈 거요, 선장님!";
				link.l1 = "고맙다, 옛 친구야.";
			}
			else
			{
				dialog.text = "잠깐, 내 말은... 아니, 내가 무슨 말을 하는 거지, 내 엉덩이에 체인 샷이라니?! 선장님, 오늘은 선장님을 위한 날이라는 뜻이었어요, 그러니까, 축하드리고... 그리고... 행복하시길 바라고... 그리고 미안해요, 선장님, 내가 너무 취해서 연설을 못 하겠네, 내 목에 체인 샷, 나 요즘 맨정신인 적이 없었거든요 하하하!\n";
				link.l1 = "하! 괜찮아... 고맙다, 옛 친구야.";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "아! 그리고, 선장님, 이것도 받아주십시오. 선장님과 부인께 드리는 겁니다. 이 보석들은 만일을 위해 아껴두었지요... 금화는 부족하지 않으시겠지만, 이런 건 많아도 나쁠 건 없겠지요?";
			link.l1 = "찰리, 너 정말 인심이 후하구나. 이 에메랄드들은 몽페르 부인 가문의 귀걸이에 정말 잘 어울릴 거야!";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "자, 그럼 그걸 위해 한잔하지, 체인 샷이 내... 흠. 그냥 행복하게 살아, 너도 네 미인도, 선장!";
			link.l1 = "그래, 찰리!";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "멋진 결혼식이었어요, 선장님!";
			link.l1 = "마시고 신나게 놀아!";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "나는 한 번도 생각 못 했소, 선장님, 당신이 결혼하는 걸 보게 될 줄은. 우리가 택한 길은 보통 외로운 길 끝에 쓸쓸한 무덤으로 이어지니까. 내 기억 속에서 그걸 벗어난 사람은 당신이 처음이오. 이건 한 잔 더 올릴 만한 일 아니겠소?";
			link.l1 = "이게 끝이야, 친구! 그리고 정말로, 내 인생에서 이 부분이 지나가서 기쁘다. 건배!";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "너희 둘의 오래오래 행복한 삶을 위해 건배! 젠장, 너희를 보니 나도 한때 결혼했던 게 생각나는군.";
			link.l1 = "너? 결혼했다고? 흥미로운 소식이군! 그런데 무슨 일이 있었던 거야?";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "뭐야, 선장, 내가 처음부터 화약 냄새와 피 냄새 풍기는 늙은 외눈박이였을 것 같나? 아니지. 마담 톤자그, 그 여자가... 날 사랑했었지, 아마도. 하지만 그 뒤로 불쾌한 일이 벌어졌어. 그 일로 톤자그 부부는 죽고, 흉터만 남은 대머리 가스통만이 살아남았지.";
			link.l1 = "미안해, Hercule, 몰랐어...";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "잊어버려, 선장. 그 이야기는 오래전에 있었던 일이야. 하지만 지금 너를 보니 내 이야기도 아직 해피엔딩이 될 수 있을 것 같아. 그러니, 그걸 위해 한잔하자!";
			link.l1 = "그래, 친구야. 있잖아, 내가 너를 처음 만난 날부터 쭉 내 아버지처럼 생각해왔어. 언젠가 네가 증조할아버지가 될 기회도 있을지 모르지. 아무튼, 건배! 나는 나머지 일도 챙겨야 하니, 나중에 얘기하자.";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "성대한 축하입니다, 선장님!";
			link.l1 = "마시고 신나게 놀아라!";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "여기 우리 선장님 오셨네! 축하해, 너랑 네 아내 정말 잘 어울리는 한 쌍이야! 두 분 오래오래 행복하게 사시길 바라!";
			link.l1 = "감사합니다, Raymond.";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Sent Pierre";
			dialog.text = "선장, 결혼식 치르기엔 너무 맑은 정신인 것 같은데? 한잔 걸치고 싶지 않아? 내가 술집에서 훌륭한 셰리를 한 병 구해왔어. 이걸 현지 럼주랑 섞으면 끝내주지!";
			link.l1 = "나도 그러고 싶지만, 여기서 누군가는 상황을 지켜봐야 해. 안 그러면, \n "+sTemp+" 아침이 되면 선술집만 그리운 게 아닐 거야.";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "훌륭한 음식에 훌륭한 럼주까지, 선장님! 당신과 젊은 아내를 위해 건배!";
			link.l1 = "고마워!";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "젊은이들, 왜 함부로 들어오는 거지? 조선소는 닫았잖아, 뻔히 보이잖아? 내일 다시 와.";
			link.l1 = "주인님, 폐를 끼쳐 죄송합니다만, 저희는 감옥을 그냥 지나가겠습니다. 결혼식에 쓸 물자가 있고, 선술집에 술이 거의 다 떨어졌거든요.";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "오, 샤를 드 모르랑 네이선 호크 그 자신들이군! 누군가의 결혼식을 축하하러 온 거지? 좋아, 가서 술이나 마셔. 젊은이들은 즐겨야 하는 법이야 - 그건 언제나 진리지. 돌아올 때 병들 흔들지나 마라 - 난 이제 잘 거니까!\n";
			link.l1 = "감사합니다, 주인님, 우리는 가장 잔잔한 강처럼 조용히 있겠습니다.";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "가만히 있지 말고, 얼른 가! 자, 선장님, 모든 게 만족스러우십니까?";
			link.l1 = "...";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "뭐야, 이게?! 자크가 '여긴 아무도 안 내려온다'고 했잖아! 위고, 다시 올라가서 다른 놈들 불러와, 우리가 길을 뚫을 테니까. 녀석들 죽여라, 얘들아!";
			link.l1 = "젠장!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "이봐, 상자들은 잊어버려라, 손님이 오셨다!";
			link.l1 = "너 같은 놈들은 잭맨이랑 같이 죽은 줄 알았는데. 좋아, 끝장을 보자!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "제기랄... 들켰다! 경보 울려라!";
			link.l1 = "길 비켜, 이 자식아!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "de Maure 나리, 안녕하십니까, 아니면 벌써 아침이 다 되었나요? 들어오시고, 앉으십시오.";
			link.l1 = "앙제랑 드 시에부! 네놈을 보게 되어 전혀 놀랍지 않군! 여자들하고만 싸울 줄 아는 하찮은 놈! 혹시 그 여자들도 묶어뒀냐?! 이제 마르티니크에서 시작한 결투, 내가 끝내주마!";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "진정해, 젊은이. 이 총 보이지? 총신이 두 개나 있거든. 내가 검술은 별로지만, 사격은 꽤 자신 있어. 칼 내려놔. 안 그러면 멋진 아가씨 둘을 놓치게 될 거야, 장담하지.";
			link.l1 = "망할 놈... 젠장할.";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "그리고 너도, 해적 나리, 무기 내려놔, 그렇지, 바로 그렇게. 이제 앉아, 와인 따라도 돼, 저기 탁자 위에 있으니까. 우리는 잠깐 기다려야겠군, 바르바종 나리가 네 친구들, 해적 남작들의 배를 다 부술 때까지 말이야. 그 다음에 너랑 내가 어떻게 우리... 흠, 갈등을 해결할지 결정하지.";
			link.l1 = "분쟁을 해결하자고? 어떻게? 결투라도 하자는 거야?";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "웃기지 좀 마, Charles. 너랑 Botot 부인 때문에 내가 골치가 많이 아팠어. 그 빚은 반드시 갚을 거다. 물론, 그녀가 너보다 훨씬 더 많은 문제를 일으켰지만... 그래도 너랑 저 위풍당당한 해적 나리가 얌전히 앉아 있으면, 내 명예를 걸고 약속하지 – 너희 아내들은 목숨을 부지할 거다. 본토의 스페인 식민지에서는 그런 노예들도 값이 나간다고 믿거든. 비공식적으로라도 말이지. 그래도 살아 있는 거 아니겠어?";
			link.l1 = "앙제랑, 넌 겁쟁이에다 개자식이고... 젠장, 너한테 어울릴 만한 말이 아직 어떤 언어에도 없구나!";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "알잖아, 선택권은 없어. 내가 약속할 수 있는 건 빨리 끝내주겠다는 것뿐이야. 그러니 이 여자들이 소중하다면 얌전히 굴고, 그들의 목숨을 살려서 네 운명도 덜 힘들게 해. 그리고, 번거롭지 않다면 문도 잠가 줘. 고맙다.";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "참으로 호전적인 숙녀들이군. 그래도 신중해야 하오. 나는 여자를 죽이는 걸 결코 좋아한 적이 없소.";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "젠장...";
			link.l1 = "죽어라, 이 개자식아!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "샤를 드 모르 선장, 호크 남작 - 이런 반가운 놀람이군! 내 소개를 하지. 모리츠 두삭, 그게 내 이름이오.";
			link.l1 = "길 비켜, 이 자식아! 내 아내 어디 있어?!";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "진정해라, 신사들! 이 총 보이지? 총신이 두 개야. 괜히 그런 별명이 붙은 게 아니지 – 나도 세이버를 좋아하긴 해... 하지만 총도 잘 쏜다, 믿어라. 칼 내려놔, 아니면 손가락 몇 개 잃을지도 몰라!";
			link.l1 = "돼지처럼 널 도살해주마, 이 쓰레기놈아...";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "하지만 자네는 이미 홀아비가 될 거야. 그거 원하지 않나? 그러니 진정하고 무기를 내려놔. 호크 남작, 제발, 문을 잠가 주시오. 우리 자리에 앉아 잠시 기다리세. 저 항구 밖에 있는 자크 바르바종이 브라더후드의 우두머리들을 처리할 때까지.";
			link.l1 = "그리고 이제 뭐지? 우리 서로 껴안고 해질녘을 향해 함께 떠나기라도 할까?";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "나는 그렇게 생각하지 않아. 네놈을 잡으면 자크가 나한테 금을 퍼부어 줄 거야. 운이 좋으면, 아마 남작이 될 수도 있겠지. 네 여자들은 풀어줄 수도 있겠지만, 너는... 유감이군. 운이 좋으면 내가 직접 너를 죽일 권리를 달라고 청할 거다, 선장. 너는 유명한 검객이니, 한번 시험해 보고 싶군. 나도 내 나름대로 고수라고 생각하거든.";
			link.l1 = "밤에 남의 집에 침입해서 잠결에 있는 여자들을 묶는 데 능한 놈이라고? 너는 벌레야, 그것도 한심한 벌레지!";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "이봐, 부인, 난 여자를 죽여본 적 없어. 나를 그런 놈으로 만들지 마, 알겠어? 선장도, 당신 남편도 불안하게 만들잖아... 젠장!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "젠장...";
			link.l1 = "죽어라, 이 자식아!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "빌어먹을 프랑스 놈, 칼이나 총알 하나도 없었냐?!";
			link.l1 = "있지, 자크, 너한테 둘 다 준비해 놨어. 솔직히, 네가 잭맨이랑 짠 수작을 알게 됐을 때 널 살려둔 걸 거의 후회할 뻔했지. 하지만 이제 그걸 바로잡아 주마.";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "네 놈, 부하들 곁에 있을 때만 용감한 거냐? 그럼 바꿔보자! 남작 놈들은 나중에 상대하겠지만, 넌 여기서 살아나가지 못할 거다, 이 쥐새끼야!";
			link.l1 = "기대했던...";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "선장님, 도와주세요, 이 야만인이 저를 납치했어요! 저... 저 집에 가야 해요 - 아마 삼촌이 이미 온 마을을 뒤집어 놓았을 거예요!";
			link.l1 = "진정해, 이쁜이, 다 괜찮을 거야. 비켜, 네 '야만인'하고 얘기 좀 해야겠어.";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "감사합니다, 선장님! 저를 구해주셨군요! 오늘 아침 이 해변에서 깨어났을 때, 저는... 이런 야만인과 결혼할 뻔했다니, 믿을 수가 없어요, 그가...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "그래, 아침은 밤의 희망이라는 수정(크리스탈)을 무자비하게 깨뜨리는 망치지. 이해하네. 하지만 그는 무스코기 부족 출신이고, 자기 땅의 엄격한 법에 따라 살아가지. 그는 네 동의를 얻어 널 데려갔고, 너희는 함께 밤을 보냈어. 그러니 이제 그의 신들 눈에는 너희가 부부가 된 거다. 자, 가서 짐을 챙기자. 몸값 문제는 내가 네 삼촌과 해결하마.";
				link.l1.go = "waitress_2";
			}
			link.l2 = "이 일에 대해 미안하오. 티칭이투는 자기 부족의 법에 따라 살지만, 좋은 사람이오. 제발, 이번 납치 이야기는 잊어주시오.";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "아내라고요? 그 신들의 눈앞에서요?! 안 돼요, 선장님, 제발 이 일에서 저를 구해 주세요! 그저... 모험이었을 뿐이에요, 그는 정말 용감하고 친절했어요, 이 촌놈들이랑은 달랐죠... 하지만 결혼이라니요? 저는 아직 오두막에서 야만인과 함께 살 만큼 어리지 않아요!";
			link.l1 = "그는 내 부하이자 가장 친한 친구야. 그러니 걱정하지 마. 나는 그에게 충분히 보수를 주고 있고, 네가 바랄 수 있는 최고의 오두막을 마련해 줄 거야. 티칭기투는 솜씨 좋은 사냥꾼이니 먹을 것을 마련해 줄 거고, 너는 아이를 낳아 기르게 될 거야.";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "아이들이요? 음식을 구하라고요?! 안 됩니다, 선장님, 제발 저한테 이러지 마십시오, 부탁드립니다!";
			link.l1 = "글쎄, 내가 그를 설득할 수 있을지도 모르지. 하지만 쉽진 않을 거야. 머스코기 부족은 이런 일에 아주 엄격하거든; 누가 그가 여자를 훔쳐가 놓고 결혼도 안 했다는 걸 알게 되면...";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "제발 해봐, 부탁이야! 아무한테도 말 안 할게, 아무도 모를 거야! 삼촌한테도 거짓말할 거야, 이번이 처음도 아니잖아!";
			link.l1 = "좋아, 가도 돼, 아름다운 스콰. 내 친구는 내가 떨어뜨려 놓을게.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "걔가 나를... 마치 헛간에서 염소 훔치듯이 데려갔어! 모두한테 다 말할 거야! 우리 삼촌이 그 자를 죽일 거야! 삼촌은 화나면 정말 무서워! 예전엔 스페인 배도 털었었거든 – 삼촌 앞에선 장난이 아니야!";
			link.l1 = "좋아, 조용히 해, 아름다운 아가씨, 조용히. 그를 용서할 만한 '이유' 이만 개가 내 말보다 더 설득력 있지 않을까? 아니면 그 돈을 네 삼촌에게 줄까, 마치 신부 몸값처럼? 어차피 모두가 이 섬에 있잖아? 내일 또 결혼식을 열 수도 있겠군...\n";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "아니, 아니요, 선장님, 잠깐만요! 설득당했어요. 삼촌이 화내지 않게 뭔가 생각해볼게요. 안녕히 가세요! 그리고 먼 평원에서 온 나의 준마여, 너에게도 작별을! 다음에 오면 꼭 다시 찾아와요...";
			link.l1 = "그래, 맞아. 동의해서 다행이군. 집에 가, 이쁜이.";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "자, 선장님, 모든 게 마음에 드십니까? 최고급 럼주, 양갈비, 돼지 햄, 거기에 과학자 친구분을 위해 제 개인 창고에서 꺼낸 훌륭한 와인까지 준비했습니다! 그리고 - 선장님과 아름다운 부인께 축하를 드립니다!";
			link.l1 = "고마워! 솔직히 말해서, 네가 모든 걸 완벽하게 준비했어. 네 지하 저장고에 럼주가 충분히 쌓여 있길 바란다, 아침은 아직 멀었으니까.";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "걱정하지 마시오, 술통이 비면 내가 조수 하나를 항구 창고로 보내겠소. 마음껏 즐기시오, 나리, 아무 걱정 말고.";
			link.l1 = "좋아, "+npchar.name+"그러면 손님들에게 가보겠소.";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "무엇을 드시겠습니까, 선장님? 갈비 튀김, 훈제 햄, 아니면 브리스킷? 혹시 부인분을 위해 와인도 필요하신가요?";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("선장과 그의 아내의 건강을 위하여!","영원히 행복하게 사시길, 선장님!","두 분 모두 오래 살고 행복하시길!"),LinkRandPhrase("선장님과 그 미녀 만세!","행운이 선장과 그의 배우자에게 평생 함께하길!","가정에 순풍이 불길 바라, 선장!"));
			link.l1 = LinkRandPhrase("고마워!","감사합니다!","건배!");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("미쳤어? 도살자라도 되고 싶었던 거야? 모든 해적들이 너한테 화났으니, 친구야, 여기서 빨리 떠나는 게 좋을 거다.","이봐, 친구, 미친 거 아니냐. 손 좀 풀어보고 싶었어? 기분 나쁘게 듣지 마, 여기서 네가 할 일은 없어. 꺼져!");
				link.l1 = RandPhraseSimple("들어봐, 내가 모든 걸 바로잡고 싶어...","문제를 해결하는 데 도와줘...");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "아, 기다리고 있었소, 보스. 얀 스벤손이 분명히 자네가 르 프랑수아의 상황을 확인하러 올 거라고 경고했지. 이제 모든 건 내가 직접 챙기고 있으니, 천둥을 걸고 맹세하건대, 이 마을은 그 빌어먹을 킨드맨 때보다 훨씬 번성할 거요. 지옥의 가장 어두운 지하실에서 악마들이 그놈을 가지고 놀게 두지!";
					link.l1 = "너, 장 다비드 맞지? 스벤손이 내 몫에 대해 뭐라고 하던데...";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" 보스. 르 프랑수아는 언제나처럼 아무 문제 없어. 왜 오신 거야? 뭔가 도와줄 일이라도 있어?";
					link.l1 = "그냥 어떻게 지내나 들러봤어.";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "내 몫은 어쩔 건데?";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+" 이봐, 무슨 일로 왔어? 뭘 도와줄까?";
				link.l1 = "그냥 인사하러 들렀어.";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "명령만 내리십시오, 보스! 몫에 관해서라면, 매달 5일마다 우리 녀석들이 벌어들인 금화 중 일부를 따로 떼어두겠소. 필요할 때까지 언제든 기다릴 테니, 다음 달부터 와서 받아가면 되오.";
			link.l1 = "좋았어!";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "나머지는 내가 알아서 할게. 숲의 악마가 그러더군, 너는 르 프랑수아 같은 하찮은 일에 신경 쓸 시간도 없을 거라고...";
			link.l1 = "제대로 들었군. 좋아, Jean, 너를 믿고 맡길 테니 실망시키지 마라.";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "다 잘 될 거예요, 보스. 여기서는 모든 게 내 손안에 있어, 하하! 내가 뭔가 망치면 평생 다시는 럼을 안 마시겠소!";
			link.l1 = "좋아, 또 보자!";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "기다리고 있었습니다, 보스. 그동안 당신을 위해 우리가 모아 두었소\n "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+". 가져가.";
			link.l1 = "하, 나쁘지 않군. 잘했어, Jean.";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "최선을 다하겠습니다, 보스. 다음 달이나 원하실 때 언제든 다시 오십시오 - 당신의 돈은 저에게 맡기면 안전합니다.";
			link.l1 = "좋아, 또 보자, Jean.";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "문제를 해결하라고? 네가 무슨 짓을 저질렀는지 알기나 해?\n어쨌든, 백만 페소를 가져와. 그러면 내가 녀석들을 설득해서 네 짓을 잊게 해주지. 그게 싫으면 지옥이나 가.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "좋아, 돈 낼 준비 됐어.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "알겠어. 나 간다.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "좋아! 이제 다시 깨끗해졌다고 생각해. 하지만 다시는 그렇게 역겨운 짓을 하지 않길 바란다.";
			link.l1 = "나는 안 할 거야. 나한텐 너무 비싸. 잘 있어...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 
