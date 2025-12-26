// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time": //первая встреча - знакомство
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "잠깐만, 잘생긴이! 우리 얘기 좀 해야 할 것 같은데.";
			link.l1 = "내가 그쪽을 아나? 뭐, 어쨌든 숙녀를 위해서는 언제나 몇 시간쯤 내줄 수 있지.";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "아직 계획 세우지 마, 선장. 몇 시간 더 젊고 어리숙해 보이는 아가씨나 찾아봐. 너한테 맡길 일이 있어. 사실 난 결혼했거든. 내 남편 이름은 네이선리얼 호크야.";
			link.l1 = "이거 참! 그럼 네가... 음, 대니 호크구나, 스벤손 나리가 너에 대해 말했지.";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "실제로 나타났군. 그래, 숲의 악마가 나를 별로 좋게 생각하지 않는다는 건 알고 있어—나도 마찬가지야—하지만 내가 이 예쁜 사브르를 그냥 멋으로만 차고 다니는 건 아니라는 걸 네게 경고해야 했지. 그러니 본론만 말해, 아들!\n나는 한동안 스벤손과 그의 방문객들을 몰래 지켜보고 있었어. 내 남편을 정글로 보내 죽게 만든 게 바로 그였으니까. 처음엔 그가 잭맨과 한패라고 생각했는데, 이제 보니 아니더군. 네가 스벤손과 얘기할 때 창문 밑에 숨어 있었지. 전부 엿듣진 못했지만, 쓸만한 정보는 꽤 얻었어.\n정말로 내 남편을 찾아주고, 잭맨을 혼쭐내줄 생각이 있는 거야? 아니면 그냥 허세 부린 거냐?";
			link.l1 = "엿듣는 건 옳지 않소, 호크 부인. 하지만 나를 좀 더 존중해서 대한다면 용서해 주겠소. 내가 호크를 찾든 말든 그건 내 일일 뿐이오. 쓸모 있는 말이 있다면 하시오, 없다면 나를 그냥 두시오. 두 번 묻지 않을 것이오.";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "아하, 참 성질 급하군! 자, 선장... 내 성미가 당신을 불편하게 하는 건 분명하겠지. 당신이 겁쟁이가 아니고, 자기 가치를 아는 사람이라는 건 알겠어. 그러니... 인사나 하자고. 앞으로는 당신에게 말 조심하겠다고 약속하지. 나도 당신이 필요하고, 당신도 내가 필요해. 우리는 같은 목표를 가지고 있잖아. 나를 선원으로 받아주면 후회하지 않을 거야. 네이선을 찾을 때까지 성실과 충성으로 당신을 섬기겠다고 맹세하지.";
			link.l1 = "받아들여졌다고 생각하게... 대니. 스벤손이 네가 이미 남편을 찾고 있었다고 말하더군. 흥미로운 걸 찾았나?";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "별로 많지는 않지만, 잭맨이 거짓말을 했다고 비난하기엔 충분해. 그 자식이 말하길, 내 남편 네이선이 맞닥뜨린 광산 경비병들은 포로를 잡지 않는다고 했지. 물론 아무도 내 남편 시신을 만에서 본 적이 없다는 건 사실이야. 하지만 그럴 수밖에 없지, 실제로는 포로로 잡혀 광산으로 끌려갔으니까. 미스키토족 주술사 스네이크 아이가 거기서 그를 발견했어.\n그가 탈출도 도와줬지. 하지만 내 남편이 지금 어디 있는지는 여전히 알 수 없어. 주술사가 쿠쿨칸이라는 자가 그를 잡아먹었다고 중얼거리던데, 나는 무슨 말인지 전혀 이해하지 못했어. 게다가, 그 원주민은 백인 여자는 자기한테 아무 의미도 없는 존재라고 분명히 했지. 당신이 직접 그와 이야기해 보는 게 좋겠어, 어쩌면 당신한테는 더 많은 말을 해줄지도 몰라.";
			link.l1 = "그거라도 다행이군! 이런 소식이 들으니 기분이 좀 나아진다. 그 인디언을 어디서 찾을 수 있지?";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "정글 깊숙한 곳에 마을이 있어. 우리는 아마티크 만에 상륙해서 정글을 서쪽으로 지나가야 해. 네가 직접 못 찾겠으면 내가 길을 안내해 줄게. 마을에서 멀지 않은 곳에 돌 우상이 있는데, 야만인들은 그걸 신처럼 숭배하지. 나도 몇 번 가본 적 있어. 별거 없어. 그냥 이끼가 낀 평범한 돌일 뿐이야.";
			link.l1 = "흥미롭군. 좋아, 가자. 주술사와 이야기해 보고 다음에 뭘 할지 정하자고. 준비됐지?";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "물론이지! 당연히 준비됐어. 마룬 타운을 떠난 이후로 계속 여행 중이었거든. 게다가, 나는 네 승객 중 한 명으로만 남고 싶지 않아.";
			link.l1 = "좋아. 내 배로 가자.";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "예, 알겠습니다, 선장님!";
			link.l1 = "...";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.CompanionDisable = true; //нельзя в компаньоны - чтобы не утонула
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; //чтобы не убили в сухопутном бою
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			//выбираем амулеты
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// на локацию с истуканом
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// у истукана в джунглях
		case "Dolly":
			dialog.text = ""+pchar.name+"! 어서 와! 인디언 주술사가 말하던 석상 보여줄게. 그냥 평범한 돌기둥이야. 가자!";
			link.l1 = "...";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "이봐! 한번 봐, 그냥 돌 조각상이잖아. 별거 없어...";
			link.l1 = "알겠네... 그런데 맨 위에 있는 인물은 좀 불길하지 않나? ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "모든 인디언 조각상들은 무섭고 음산하게 생겼어. 전에 비슷한 걸 본 적이 있지. 다 똑같더라. 아무튼, 가자, 마을이 바로 근처야!\n";
			link.l1 = "가자!";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// у мискито
		case "SnakeEye":
			dialog.text = "그래서, 어떻게 생각하시오, "+pchar.name+"? 그 붉은 피부의 복화술사가 너한테 뭐라고 했지? 그의 철학적인 말에서 뭔가 건졌냐?";
			link.l1 = "또 엿듣고 있었냐, 대니?";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "음... 조금은 그래. 알잖아, 우리 여자들은 원래 이런 걸. 하지만 이해해 줘야 해 – 난 그냥 내 남편이 걱정돼서 그래. 사실 정말 사랑하거든. 그러니까 내가 엿들었다고 뭐가 어때서? 아무튼, 쓸만한 정보라도 얻었어?";
			link.l1 = "생각해 보려고 하는데... 스네이크 아이를 이해하는 게 쉽지 않았지. 하지만 우리가 마을로 들어올 때 봤던 그 우상은 사람을 순간이동시키는 일종의 마법 포탈인 것 같아.";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "나를 그렇게 쳐다보지 마. 이건 내 생각이 아니었고, 지금까지 내 머리는 아무 문제 없었어. 네가 주술사가 뭐라고 했는지 물었으니, 내가 말해주는 거야.";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "부디, 용서해 주십시오. 더 이상 그렇게 쳐다보지 않겠습니다. 계속하시지요.";
			link.l1 = "그가 말하길, 네이선이 추격자들에게 거의 붙잡힐 뻔했을 때, 인디언이 그를 구하기 위해 조각상을 보여주며 그것을 쿠쿨칸이라 부르고, 네이선을 통째로 삼켰다가 다른 곳에 뱉어냈다고 했소. \n간단히 말해, 네이선은 그 조각상에 의해 순간이동을 한 것 같소.";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "이런, 뭐야... 나랑 네이선은 이미 비슷한 곤경을 겪은 적이 있는데, 또 이런 일이 벌어지네. 마야의 마법으로 가득한 그 인디언 사원에서 충분히 모험을 했었는데...\n";
			link.l1 = "방금 뭐라고 했지?";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "아, 아무것도 아니야, "+pchar.name+", 상관없어. 그냥 내 거친 젊은 시절의 추억일 뿐이지. 그런데 네이선은 어떻게 그런 일을 할 수 있었지? 그러니까, 순간이동 말이야? 우리는 그 우상 근처에 있었고, 나는 그 주위를 돌아다니며 만지고 있었어... 그저 돌덩어리일 뿐인데!";
			link.l1 = "스네이크 아이가 자정이 되면 우상이 살아난다고 말했어. 그때서야 쿠쿨칸의 영이 깃들면서 황금빛으로 빛나기 시작하지. 그때는 절대 손대지 말아야 한대. 아니면, 어쩌면 그때야말로 손대야 할지도 모르지...";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "으스스하군... 이제 어쩔까? 자정까지 기다렸다가 정글로 들어갈까?";
			link.l1 = "아니. 주술사가 말하길, 그 우상은 사람을 순간이동시킬 뿐만 아니라 그들의 생명도 빼앗는다고 했어. 내가 이해한 바로는, 그건 곧 체력을 소모시킨다는 뜻이었지. 스네이크 아이는 저 동상을 세 번이나 통과했고, 매번 순간이동할 때마다 무슨 특별한 약으로 스스로를 치료했어.";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "그에게 이 물약을 요청해 보았소?";
			link.l1 = "물론이지. 하지만 첫째로, 플라스크가 세 개밖에 안 남았고, 둘째로, 그가 그것들과 맞바꾸자며 부적 세 개를 요구했어.";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "물약 없이 이 일을 해보는 건 어때? 밤에 그 동상에 가서 만져보자...";
			link.l1 = "너무 위험해. 인디언이 약간 제정신이 아니고 우리를 속이고 있다는 건 인정하지만, 사이코패스처럼 보이지는 않으니 진실을 말하고 있다고 믿네. 자네가 인디언 마법에 대해 뭔가 말했던 게 기억나는데... 그 존재를 의심하나?";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "그래, 내가 그랬어. 내 두 눈으로 직접 봤으니 의심할 여지가 없어. 그러니 네 말이 맞아, 굳이 위험을 감수할 필요는 없겠지.";
			link.l1 = "정확히 그렇지. 그래서 우리가 먼저 부적을 찾아낼 거야, 그 다음 주술사에게서 그 멋진 물약을 받아서 조각상으로 갈 거다. 내가 갈 거야. 혼자서.";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "그게 왜지? 그리고 나는 어쩌라고?";
			link.l1 = "내가 없는 동안 네가 내 배에 남아 책임을 져야 해. 말대꾸하지 마, 대니. 물약은 딱 세 병뿐이야. 만약 주술사가 맞고 이게 정말 작동한다면, 포탈이 어디로 이어지는지도 알 수 없어. 어쩌면 그곳에서 네이선조차 찾지 못할 수도 있어.";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "너도 네이선이랑 똑같아. 남자란 다 똑같지... 좋아, 알겠어.";
			link.l1 = "서로 이해하게 되어 다행이군. 이제 가자, 부적을 찾아야 하니까.";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед походом к истукану
		case "teleport":
			dialog.text = "그래서 뭐? 물약은 구했어?";
			link.l1 = "그래. 물약이랑 몇 가지 지시도 받았어. 이제 남은 건 자정에 우상에게 가서 그걸 만지는 것뿐이야.";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "겁나냐?";
			link.l1 = "예. 주술사가 단순히 미친 사람일 뿐이고, 순간이동 따위는 일어나지 않을까 봐 걱정이오.";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "그래, 그래... 정말 무섭지도 않아? 조금도 안 무서워?";
			link.l1 = "대니, 너무 몰아붙이지 마... 정말 알고 싶다면, 그래, 솔직히 말해서 자신이 별로 없어, 고백하자면.";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "당신과 함께 가겠소.";
			link.l1 = "또 다시 말싸움할 셈이야? 우리 합의 본 줄 알았는데...";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "나를 오해했군. 나는 그냥 네 곁에만 있을 거야. 그 조각상이 제대로 작동하는지... 아니면 그렇지 않은지 확인해야 하거든.";
			link.l1 = "이의는 없어. 하지만 만약 그 조각상이 날 '잡아먹는다'고 해도 따라올 생각은 절대 하지 마. 알겠어?";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "그래요. 따라가지 않겠다고 약속해요... 선장.";
			link.l1 = "좋아. 그리고, 대니, 네가 소문만큼 못된 년은 아닌 것 같군.";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "너는 나를 잘 모르는군, "+pchar.name+". 하지만 지금은 그 이야기는 하지 맙시다.";
			link.l1 = "...그러지 말자... 자, 밤에 떠날 준비를 하자!";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// перед телепортацией
		case "shadowstar":
			dialog.text = "봐, "+pchar.name+"! 맹세코, 저 동상 위에 이상한 빛이 떠 있소!";
			link.l1 = "주술사가 거짓말을 한 것 같지는 않군. 그리고 어둠이 나를 속이지 않는다면, 저 동상 꼭대기가 더 이상 그렇게 돌처럼 보이지 않는 것 같은데.";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "정말이야... 순금으로 만들어진 것처럼 보여! 믿을 수가 없어!";
			link.l1 = "때가 왔어, 대니. 행운을 빌어 주고 손가락도 꼬아 줘. \n우상 근처엔 가지 마! 여기 있어.";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "행운을 빌어요, "+pchar.name+"... 잘 되길 바라자... 주술사의 물약은 준비했나?";
			link.l1 = "그래, 여기 있어. 다니, 다 잘 될 거야. 자, 간다! (T를 눌러 우상을 활성화하세요)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// прибыл назад 
		case "arrive":
			dialog.text = "아-아-악?! 젠장! 대체 넌 무슨 괴물이냐, 젠장할?! 지옥에나 떨어져라! 내 평생 별별 괴물 다 봤다, 반 데르 데켄 그 자식까지 포함해서! 이제 네가 원하는 걸 보여주마!";
			link.l1 = "(희미하게) 대니, 기다려! 그만둬! 지금 당장!";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "(희미하게) 반 데르 데켄? 흐-하-하-하! 그 벌레는 이미 내 밑에서 일하고 있지! 이제 네 차례다! 내 앞에 무릎 꿇어라, 충실한 종이여! 네가 내 언데드 군대를 이끌게 될 것이다!\n";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "아-아-아-아-아-아-아-아-아-아-아-아! 저리 가! 지금 이럴 수는 없어!";
			link.l1 = "(희미하게) 대니, 기다려! 그만해! 지금 당장!";
			link.l1.go = "arrive_1";
		break;
		// <-- legendary edition
		case "arrive_1":
			dialog.text = "아?! 뭐라고 했어?! 대니?";
			link.l1 = "(희미하게) 당장 그만둬! 검을 거둬! 이것 좀 벗게 해 줘!";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "젠장, 이 괴물아, 목소리가... "+pchar.name+"?!";
			link.l1 = "(희미하게) 오... 정말이야!";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "이런 젠장, 너 때문에 거의 죽을 뻔했잖아! 방금 내 검으로 널 베어버릴 뻔했다고!";
			link.l1 = "나도 봤어... 그런데 왜 그렇게 불타오르냐, 응?";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "그게 바로 나야... 아, 아직도 가슴이 두근거려서 미칠 것 같아...";
			link.l1 = "대니, 지금 우리가 어디쯤이지? 미스키토 마을에서 멀지 않은 거 맞지?";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "우리가 또 어디에 있을 수 있겠어! 이게 바로 널 사라지게 만든 동상이야. 정말 장관이었어! 평생 잊지 못할 거야.";
			link.l1 = "그렇군, 여기서 내내 나를 기다리고 있었던 거야?";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "말해 봐, 내가 달리 뭘 할 수 있었겠어? 그 동상이 널 삼켜버린 뒤엔, 언젠가 널 다시 뱉어내길 바라는 수밖에 없었지. 게다가 스네이크 아이가 이게 가장 가능성 높은 결과라고 했거든.\n나는 미스키토족과 함께 살면서 매일 그 우상을 지켜봤어. 우리가 왜 이런 헛소리를 하고 있는 거지? 말해 봐! 거기서 무슨 일이 있었던 거야? 어디에 있었던 거야?";
			link.l1 = "대니, 이 이야기는 너무 길어, 내가 겪은 게 정말 많거든... 하지만 속을 털어놓자면, 내가 네이선리얼을 찾았다는 걸 말해줄게!";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "네이선을 찾았어? 어디 있지? 그리고 괜찮아?!";
			link.l1 = "거짓말하지 않겠소 - 그는 살아 있소, 하지만 상태가 매우 안 좋소. 코만치의 묘약도 없었고, 우상 때문에 모든 기운이 빠져버렸소. 그는 이상한 버려진 배들의 섬에 있는 낡고 부서진 배의 선실에 누워 있소. 나도 그곳으로 순간이동됐으니, 스네이크 아이가 옳았던 거요!";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "가엾은 네이선... 그 빌어먹을 섬은 어디에 있는 거지? 어떻게 가는 거야?! 오직 그 우상만이 길인가? 미스키토족한테서 치료약을 전부 사서 오늘 밤에 가볼 거야! 어떻게든 해낼 거야...";
			link.l1 = "멈춰! 기다려! 네이선은 아프지만 생명에는 지장이 없어. 한 녀석이 그를 돌보면서 먹을 것도 주고 있어. 만약 우상을 통과하면 네 건강이 망가질 거야, 그리고 이 섬은 정말 위험해. 너무 위험하다고!\n";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "그럼 어쩌자는 거요? 네이선이 고통받고, 어쩌면 죽어가고 있는데 우리가 가만히 있으란 말이오?";
			link.l1 = "흥분 좀 그만해. 첫째, 내가 네이선이 아프다고 했지 죽는다고는 안 했어. 내가 직접 그와 얘기했으니까. 둘째, 나는 그 섬으로 항해할 거고, 너도 나랑 같이 갈 거야.";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "그 섬이 어디 있는지 아시오?";
			link.l1 = "그럼, 알고 있지! 거기서 네이선뿐만 아니라 샤크 돗슨도 찾았어. 섬의 대략적인 좌표와 그 주변 암초를 피하는 항로도 알아냈지. 이제 내 배로 돌아가서 블루웰드로 항해할 거야...\n";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "무슨 이유지? 왜 지금 바로 그 섬으로 항해할 수 없는 거야?";
			link.l1 = "대니, 원정을 준비해야겠어. 섬에 식량이 심각하게 부족하니 최대한 많은 식량을 사들일 거야. 그 다음엔 그 섬의 암초를 통과할 수 있는 배를 골라야 해. 모든 배가 그 섬까지 갈 수 있는 건 아니거든. 그리고 먼저 스벤손하고도 얘기하고 싶어...";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "준비하는 데 오래 걸리지 않을 거야. 그 섬은 여기서 멀지 않아, 아바나 북서쪽이자 멕시코만 동쪽에 있지.";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "좋아... 그럼 이렇게 하지. 네가 네이선을 찾았으니 그게 가장 중요한 일이야. 고마워! 거기서 네이선이 몸이 안 좋은가?";
			link.l1 = "음... 그분은 아프셔. 게다가 우울하고 절망에 빠져 있지. 당신을 그리워하고 있어. 그리고 그래, 네이선이 꼭 전해 달라고 했어. 당신을 아주 많이 사랑한다고.";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(눈물을 훔치며) 늙은 바보! 내 말은 한 번도 안 들었지... "+pchar.name+", 네 배로 가자! 최대한 빨리 출항하고 싶으니까!";
			link.l1 = "그래, 대니. 그리고 내 모험 이야기도 들려줄게. 가자!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // пускать офицеров в локу телепорта
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			setCharacterShipLocation(pchar, "Shore9"); // калеуче
			setWDMPointXZ("Shore9"); // корабль в бухту Аматике
			bNoEatNoRats  = false; // еду и крыс включить
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// в LSC у причала
		case "nathaniel":
			dialog.text = "이런 곳은 처음 봐. 섬 전체가 배로 만들어졌잖아!";
			link.l1 = "내가 그 얘기 했잖아, 대니...";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "하지만 이제 내 두 눈으로 직접 볼 수 있군. 아무튼, 네이선리얼이 어디 있는지 말해 줘.";
			link.l1 = "그는 배들 중 하나 안에 있어. 하지만 네가 헤엄쳐서 가야 해.";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "상관없어. 그 배로 어떻게 가는지 말해.";
			link.l1 = "대니, 진정해. 너랑 네이선 둘 다 오래 기다렸으니 조금만 더 참아! 내가 그에게 데려다줄게; 너 혼자서는 절대 못 찾아. 네가 혹시 나월이나 리바도스랑 마주치면 싸움만 나고 좋을 게 없어.";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "좋아, 그럼 가자. 내가 따라갈게.";
			link.l1 = "수영을 많이 해야 한다는 걸 잊지 마.";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "괜찮아, 내가 알아서 할 수 있어.";
			link.l1 = "그 소식을 들으니 기쁘군... 곧 남편을 만나게 될 거요!";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// следующая нода
			if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // иначе Мэри
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // иначе завершение
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "네이선리얼... 네이선! 젠장! 내 사랑...";
			link.l1 = "...";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;//лоченые интерфейсы
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "이런, 너 자신을 좀 봐... 왜 그렇게 한 거야?!..(울면서) 넌 내 말을 절대 안 들어, 절대! 내가 그 정글에 가지 말라고 했잖아! 그런데도 결국 갔지! 왜, 네이선?!";
			link.l1 = "대니... 미안해. 어쩔 수 없었어, 너도 알잖아...";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "나도 알아! 오, 세상에, 자기야... 무슨 일이 있었던 거야! (눈물을 흘리며) 괜찮아, 자기야, 다 잘 될 거야... 내가 여기 있어. 우리가 너를 미스키토족에게, 스네이크 아이에게 데려갈게. "+sld.name+"  주술사가 너를 치료할 수 있을 거라고 하더군. 우리에겐 배도 있어... 다 잘 될 거야!";
			link.l1 = "대니, 자기야... 내 사랑! 당신이 곁에 있어도 내 상처는 반쯤만 아물었어. 당신이 가자는 곳이라면 어디든 갈게. 스네이크 아이에게 가자면, 그리로 가지.";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "짐을 챙겨라. 아, 내가 정말 바보구나... 빈 병 말고 챙길 것도 없잖아. 네이선...";
			link.l1 = "대니...";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // перекидываем pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+" ... 네이선과 저의 소란을 용서해 주십시오.";
			link.l1 = "대니! 뭘 용서하라는 거야? 괜찮아. 네 감정이 부끄러운 거야?";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "아니, 나는 아니야... 그냥...";
			link.l1 = "이 장면에 대해선 아무도 절대 알지 못할 거야. 약속하지. 그리고 네이선에게 무슨 일이 있었는지도 아무도 모를 거야. 마룬 타운의 해적들은 강하고 두려운 네이선리얼 호크만 보게 될 거야!";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "감사합니다, "+pchar.name+"! 내가 신세를 졌어... 남편을 배로 데려갈게. 걱정 마, 내가 그곳까지 데려갈 수 있어. 길도 기억하고 있으니까. 침대에 눕히고 곁에 있을 거야. 여기서 네가 할 일 다 끝나면 우리 스네이크 아이로 떠나자. 나는 그가 회복할 수 있다고 믿어, 네이선.";
			link.l1 = "좋아, 대니. 어차피 여기 오래 머물 일도 없으니. 정말로 도움이 필요 없겠어?";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "확실해. 우린 배에 도착할 거야. 걱정 마, 내 남편이 죽게 두지 않을 거니까!";
			link.l1 = "대니, 너는... 정말 멋져!";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(눈물을 훔치며) 가... 그냥 가, "+pchar.name+"... 그리고 여기서 시간 낭비하지 마시오!";
			link.l1 = "...";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableCharacterMenu = false;//лоченые интерфейсы
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// открываем вход к Мэри
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; //открыть карту
				DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			}
		break;
		
		case "treatment":
			dialog.text = "그래서 뭐? 그 사람이 내 남편을 고쳐 줄 건가? 말해 봐, 정말 고쳐 줄 거야!";
			link.l1 = "대니, 네이선은 여기 남아 있어야 해. 혼자서. 주술사가 의식을 치르는 동안 방해하지 말라고 했어. 너도 마찬가지야. 주술사가 한 달 안에 네이선이엘을 치료해 주겠다고 약속했어.";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "있잖아, "+pchar.name+", 이제야 비로소 숨을 제대로 쉴 수 있겠어요. 저는 주술사가 제 남편을 원래대로 돌려놓을 거라고 굳게 믿어요. 만약 스네이크 아이가 남편을 고치지 못한다면 그 누구도 할 수 없으니, 저는 주저 없이 네이선을 여기 두고 가겠어요.";
			link.l1 = "다 괜찮을 거야, 대니. 스네이크 아이는 나한테 거짓말한 적 없어. 난 그를 믿어.";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "나도 그래. 당분간 너와 함께 있을게, "+pchar.name+", 그거 괜찮겠어? 아직 그 자식 잭맨을 찾아야 하잖아. 결국 모든 문제의 원흉이 그놈이야. 매복도 그놈이 꾸몄고! 마룬 타운에서 네이선 대신 자리를 차지한 것도 그놈이고! 우리 프리깃 '센튜리온'을 훔쳐 간 것도 그놈이야!";
			link.l1 = "동의하오. 잭맨을 처리해야 하오. 잭맨이 죽기 전까지 우리 중 누구도 안전하지 않소. 하지만 그를 죽이는 건 쉽지 않을 것이오.";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Shark Dodson";
			else sTemp = "Marcus Tyrex";
			dialog.text = "계획이라도 있나, "+pchar.name+"?";
			link.l1 = "아직 아니야. 얀 스벤손에게 가서 조언을 구해야 해. 한 번에 한 가지씩 하자, 우리가 진급해야 하니까\n "+sTemp+" 먼저 카리브 해적단의 수장에게 가야 해. 그러려면 모든 해적 남작의 표를 받아야 해.";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "좋아, 스벤손에게 가자. 그 늙은이 말이나 들어보자...";
			link.l1 = "있잖아, 그렇게 얀에게 부정적으로 굴 필요 없어. 사실 그와 화해하는 게 훨씬 나을 거야... 어차피 우리 모두 같은 목표를 가지고 있으니까!";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "하지만 너를 존중해서지... 좋아, "+pchar.name+", 미안하오. 스벤손을 모욕하려던 건 아니었소, 그냥 긴장해서 그랬소. 다시는 이런 일 없을 것이오.";
			link.l1 = "좋아. 대니, 모든 게 잘 될 거야. 내가 약속할게!";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "나는 너를 전적으로 믿어. "+pchar.name+". 스벤손에게 갈까?";
			link.l1 = "가자, Dannie!";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "예? 듣고 있소. 무엇을 도와드릴까?";
			link.l1 = "잭맨이 어디에 숨어 있을지 짐작 가는 데라도 있나? 너는 그 자식에 대해 나보다 더 잘 알잖아. 혹시 따로 숨겨둔 곳이나 근거지라도 있는 건가...";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "나도 모르겠어! 제이콥은 항상 비밀스러웠거든. 그 녀석의 아지트 같은 건 들어본 적도 없어. 논리적으로 생각해보는 게 낫겠지... 네가 나이브한테서 받은 편지를 다시 읽어보자. 거기서 뭔가 단서를 찾을 수도 있겠지.";
			link.l1 = "한번 해보자...";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "음... 이슬라 테소로와 어떤 유언장이 언급되어 있는데... 익숙한 이야기인가?";
			link.l1 = "얀과 나는 블레이즈 샤프가 이슬라 테소로에서 잭맨에게 살해당했고, 그 죄를 샤크가 뒤집어썼다고 생각해. 그리고 유언장... 그 계집... 헬렌에 관한 게 틀림없어... 젠장, 왜 진작에 눈치채지 못했지! 이 자식, 분명 이슬라 테소로 근처에서 항해하고 있을 거야!";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "그럼 시간 낭비하지 말자, "+pchar.name+"?";
			link.l1 = "그래. 이슬라 테소로로 가자. 이번 습격엔 늙은 '마를린'이 우리를 도와줄 거야.";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// ставим прерывание на Исла-Тесоро
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "그 자식이 드디어 죽었군... 믿기지 않아 - 내가 다시 '센튜리온' 갑판에 서 있다니! 여기 못 하나하나까지 다 아는데, 배도 나를 알아본 것 같아.";
			link.l1 = "그녀는 다시 네 것이야, 대니. 너와 네이선의 것이지.";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "내가 얼마나 기쁜지 너는 상상도 못 할 거야. 네이선리얼이 우리 배 이야기를 자주 했었지; 이제 다시 우리가 갖게 됐다는 걸 알면 정말 기뻐할 거야.";
			link.l1 = "이제 어떻게 할 거야, 대니?";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "나? 나는 배를 샤프 타운으로 가져가 최소한의 선원이라도 구해서 블루웰드로 갈 거야. 얀 스벤손에게 '센추리온'을 맡아 달라고 부탁하고, 미스키토족에게 가서 스네이크 아이가 내 남편을 치료할 때까지 거기서 기다릴 거야.";
			link.l1 = "정말로 얀 스벤손을 찾아갈 생각이오? 놀랍군...";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+", 이 모든 게 다 네 덕분이야. 네가 했던 말이 계속 생각나더라. '우린 모두 같은 목표를 가지고 있다'고 했잖아? 기억하지? 나도 이제 스벤손과 화해하고 싶어. 결국 그가 네이선을 내게 돌려줬으니까. 이제 그만 다툴 때가 된 것 같아.";
			link.l1 = "현명한 말이야, 대니! 네이선이 몸이 좀 나아지면 바로 마룬 타운에서 자기 자리를 되찾을 수 있을 거야.";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "아마도... 그게 말이야, 해적 남작은 선출직이거든. 다른 녀석들이 반대하면 어쩌지?";
			link.l1 = "스벤손에게 맡기자. 그 녀석은 누구든 설득할 수 있어. 잭맨을 제거하는 것도 한몫할 거야.";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "좋아. 어차피 스벤손과 친구가 되어야 하니까... "+pchar.name+"! 당신이 나와 네이선을 위해 해준 모든 일에 감사드리고 싶어요. 당신 덕분에 남편을 구했고, 우리가 잃었던 모든 것을 되찾았어요. 당신에게 큰 빚을 졌어요.";
			link.l1 = "어서 와, 대니. 우린 친구잖아.";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "마룬 타운에서는 언제나 당신을 반길 것이란 걸 알아두시오. 시간 나면 그곳에서 우리를 찾아오시오. 네이선과 내가 반드시 보답할 방법을 찾겠소.";
			link.l1 = "이런, 대니! 기꺼이 초대 받아들이지. 앉아서 술 마시고, 너랑 네이선이 어떻게 반 데르 데켄을 침몰시켰는지 이야기나 해보자고...";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "그가 말했나? 아, 그 얘기는 하지 마...";
			link.l1 = "좋아, 대니. 네 앞에 할 일이 많겠구나. 나는 우리의 맹우인 마르쿠스와 바르바종을 만나러 가야 해. 이 선실을 샅샅이 뒤져도 괜찮겠지? 잭맨의 상자들엔 흥미로운 것들이 잔뜩 있을 것 같거든.";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "물론이지, 내가 정말 반대할 거라고 생각해?";
			link.l1 = "좋아. 사실 너랑 헤어지는 게 아쉽네, 대니... 마룬 타운에서 보자!";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // если сработало
			pchar.GenQuest.CannotTakeShip = true; // нельзя захватить
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// в Марун-Тауне
		case "marun_town":
			dialog.text = ""+pchar.name+", 다시 만나서 정말 기뻐요! 우리는 마룬 타운으로 돌아왔고 네이선이 다시 제자리를 찾았어요. 사실 마을 사람들 모두가 그 사실에 기뻐하고 있답니다. 이제 모든 일이 예전처럼 잘 풀릴 거예요! 당신의 이타적인 도움에 진심으로 감사드려요!\n선물을 드리고 싶어요. 여기, 받아요. 이 부적은 전투를 훨씬 쉽게 만들어 줄 거예요. 그리고 이 조제법으로 당신이 직접 더 많이 만들 수 있을 거예요.";
			link.l1 = "고마워, Dannie!";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("You have received a talisman");
			Log_Info("You have received the recipe of the talisman");
			PlaySound("interface\important_item.wav");
			dialog.text = "그게 전부가 아니오. 여기서 금으로 가득 찬 궤짝 두 개도 찾았소. 분명 잭맨의 소유였을 게요. 내 감사의 표시로 이것들을 가져가시오. 거절할 생각은 하지도 마시오! 나와 네이선을 도와주느라 당신이 얼마나 많은 돈을 썼는지 내가 잘 아니까.";
			link.l1 = "좋아, 좋아, 대니, 받아들일게!";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("You have received two chests with doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "훌륭하군! "+pchar.name+", 이제부터 당신은 우리 최고의 친구라는 걸 알아줬으면 해. 네이선과 나는 언제나 마룬 타운에서 당신을 반길 거야! 자주 놀러 와!";
			link.l1 = "고마워! 다시 만나게 되면 정말 반가울 거야, 기대하고 있어!";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "무엇을 도와드릴까요, "+pchar.name+"?";
				link.l1 = "아, 나는 이제 막 떠나려는 참이야... 잘 있어, 대니.";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "자, 여기 있소 "+GetFullName(pchar)+". 네 얼굴만 봐도 시간을 허투루 쓰지 않았다는 걸 알 수 있군!";
					link.l1 = "인정해야겠군, 정말 잘 노는 법을 아는구나! 고맙네, 아주 즐거운 시간이었어.";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "다시 만나게 되어 기쁩니다, "+pchar.name+"! 럼, 와인? 아니면 아가씨?";
			link.l1 = "고마워, 대니! 그냥 너를 보고 싶었어...";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "그 여자애? 조용히 해, 대니! 내가 토막 나서 네 문 앞에 가지런히 접혀 있는 꼴을 보고 싶진 않겠지? 하하. 문 바로 밖에 서 있는 내 충직한 아가씨가 그런 짓을 용서하지 않을 거야.";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "여자라고? 흥미로운데, 대니. 난 요즘... 여인의 심장 소리가 그리웠거든... 한번 가서 봐야겠어. 아무나 추천하는 건 아니겠지, 그렇지?";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// Данни предлагает девочку
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "정말이야? 왜 이렇게 창백해? 하하, 그냥 농담이었어. 그녀 잘 챙겨, 알겠지?";
			link.l1 = "물론이지. 이 근방의 모든 보물보다도 그녀가 내게는 더 소중하니까!";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "그게 훨씬 낫군, 하하. 어서 가, 네 애인이 아마 초조해하고 있을 거야.";
			link.l1 = "잘 가라, 대니. 그리고 걱정해줘서 고맙다, 하하.";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "장담하건대, 이 젊은 미녀는 분명 잊지 못할 시간을 선사할 줄 안다오, "+pchar.name+". 즐기세요! 그녀가 선술집 방에서 기다리고 있을 거예요.";
			link.l1 = "고마워, 대니. 지금 바로 갈게. 한 순간도 낭비하고 싶지 않아!";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+", 마룬 타운에서는 언제나 환영이야. 최고의 아가씨들은 네 거다!";
			link.l1 = "오, 대니. 맹세컨대, 여긴 내 두 번째 집이야.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); //открыть комнату
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// Диалог с проституткой
		case "MarunFuckGirl":
			dialog.text = "그리고 여기 내 선장이 왔네. 오늘은 당신만 내 거야! 이리 와, 정말 오래 기다렸어...";
			link.l1 = "오, 그런가? 더는 못 기다리겠어? 그럼, 시간 낭비하지 말자!";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); //закрыть комнату
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("선장님... 정말 여인들을 사로잡는 법을 아시는군요! 이런 경험은 처음이에요! 혹시 몇 시간만 더 머물러 주실 수 있나요?","벌써 가려고, 내 사랑?");
			link.l1 = RandPhraseSimple("당신이 이렇게 쉽게 날 보내주지 않을 거란 걸 알았지. 안녕, 자기야. 위대한 일들이 날 기다리고 있어...","아아, 일이 방해가 되는군. 하지만 언젠가 다시 만날 수 있을지도 모르지...");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ------------------------------------------- провалы Саги ------------------------------------------------
		case "failcenturion":
			dialog.text = "마침내 네이선과 나는 다시 숨을 쉴 수 있게 되었어! 그 빌어먹을 자식 잭맨이 죽었거든! '센츄리온'이 아깝긴 하지만, 그 자식이 내 배를 빼앗아 갔을 때 이미 잃었다고 생각했지. 그래서 너무 신경 쓰진 않아.";
			link.l1 = "하지만 나는 알아. 나는 바보야! 모든 증거가 배와 함께 바다 밑바닥에 가라앉아 버렸어. 그 증거가 새로운 해적 연맹 수장 선출 투표에 도움이 될 수도 있었는데. 이제... 다 끝장이야.";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "너무 속상해하지 마세요! 이런 일도 있는 법이죠. 다음엔 더 운이 좋을 거예요... 아무튼, 저와 네이선을 위해 해주신 일에 감사드리고 싶어요. 당신 덕분에 제 남편이 목숨을 건졌어요. 정말 큰 빚을 졌네요.\n마룬 타운은 언제나 당신을 환영할 거라는 걸 알아주셨으면 해요. 시간 나실 때 저와 네이트를 꼭 찾아오세요. 꼭 은혜를 갚을 방법을 찾을게요.";
			link.l1 = "좋아, 대니. 꼭 찾아갈게. 벌써 떠나는 거야?";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "그래, 미스키토족에게 갈게. 스네이크 아이가 이미 네이선을 치료했길 바라. 그러고 나서 우리는 마룬 타운으로 돌아가자.";
			link.l1 = "헤, 벌써 네가 너무 익숙해져서 이렇게 헤어져야 한다니 아쉽구나... 행운을 빌어, 대니!";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "아, 모르는 척하지 마, 이쁜이. 샤를, 이 사랑꾼이 그 우상 주위를 밤낮으로 맴돌면서 불쌍한 스네이크 아이를 질문으로 들볶았지. 그리고 집에 달려가서 뭔가를 가져다줬잖아, 맞지?";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "오, 멋진 구경거리였어, Charles. 마룬 타운 전체가 이 소문으로 떠들겠는걸, 하하!";
			link.l1 = "의심할 여지 없이 이제 그 일이 당신의 최우선 과제가 되었겠지. 반드시 이루어지도록 하시오.";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "사실 내 목록 중에서도 맨 마지막에 있지. 그 소녀한테 화내지 마. 처음이거든. 나와 네이선이 모험을 했을 때도, 군도 전체가 우리를 비웃었으니까.";
			link.l1 = "화제를 바꾸고 분위기도 바꾸자. 이 우상은 이제 끝났으니, 가자.";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "알겠어, 가자, 영웅.";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Danielle_officer":
			dialog.text = "무슨 일이십니까, 선장님?";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "대니, 너에게 조언을 구하고 싶어!";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "내 명령을 들어라!";
            Link.l1.go = "stay_follow";
			link.l2 = "별거 아니오. 해산!";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл						 
		break;
		
		case "stay_follow":
            dialog.Text = "명령이오?";
            Link.l1 = "여기 서 있어!";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "나를 따라와서 뒤처지지 마!";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "화기의 탄약 종류를 변경하시오.";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "탄약 종류 선택:";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "태도가 변했다!";
            Link.l1 = "해산!";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "태도가 변했소!";
            Link.l1 = "해산!";
            Link.l1.go = "Exit";
        break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------
		
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
