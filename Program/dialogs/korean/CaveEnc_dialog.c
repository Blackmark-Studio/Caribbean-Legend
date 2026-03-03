// пещерные энкаунтеры
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, sGroup;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	sTemp = "CaveBandos" + locations[FindLocation(npchar.location)].index + "_";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭐 원하는 거 있어?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "CaveBanditosSit":
			if (hrand(2) == 1) 
			{
				dialog.text = NPCStringReactionRepeat("오호, 이게 누구야! 오늘은 네 운 좋은 날이네, 친구. 우리는 착한 놈들이야, 그냥 밥이나 해먹고 있었지... 저녁에 초대하는 건 아니니까, 아직 기회 있을 때 얼른 꺼지는 게 좋을 거다.","이제 꺼져, 우리 귀찮게 하지 말고. 내일 다시 와라 – 그리고 지갑 꼭 챙겨오라고, 하하하!","나를 화나게 하지 마, 선원! 아직도 동굴 입구가 어디 있는지 기억하지? 지금 당장, 아주아주 빨리 거기로 가야 할 거야...","이봐, 이제 선을 넘었군, 친구! 내 일거리 좀 제쳐두고 네놈을 직접 상대해야겠어, 이 자식아!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("정말 친절하군, 친구...","보아하니 너 꽤나 농담 잘하는 놈이구나...","좋아, 그럼 네 팬케이크나 계속 부쳐라...","이제야 제대로 말하는군, 하하!",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("이런, 이런! 사냥하러 갈 필요도 없네 - 먹잇감이 벌써 여기 있잖아... 이봐, 얘들아 - 저 망나니 좀 털어볼까?","여기 아무도 널 초대한 적 없어, 이 친구야... 그래도 네가 와서 다행이지. 어디 보자, 네 돈주머니가 얼마나 무거운지 확인해볼까!","아무도 널 억지로 여기 끌고 온 건 아니지, 헤헤... 하지만 이미 온 김에, 네 주머니에서 뭐가 떨어지나 좀 간질여 볼까...\n");
				link.l1 = LinkRandPhrase("이제 네 혀를 좀 잘라주지...","네 입만큼 칼 솜씨도 뛰어나길 바란다, 수다쟁이!","그래, 이제 네 썩어 없어질 몸뚱이에 구멍을 몇 개 더 내줄 시간이군...");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveBanditosSit";
		break;
		
		case "CaveBanditosStay":
			dialog.text = LinkRandPhrase("이런, 세상에! 사냥하러 갈 필요도 없겠군... 먹잇감이 벌써 여기 있어! 이봐, 얘들아 - 저 멋쟁이 좀 털어볼까?","여기 아무도 너 초대 안 했어, 이 친구야... 그래도 온 건 잘됐지. 어디 보자, 네 주머니가 얼마나 무거운지 확인해볼까!","아무도 널 억지로 끌고 온 건 아니지, 크크... 하지만 이미 여기 왔으니, 주머니에서 뭐가 나오는지 좀 간질여 볼까...\n");
			link.l1 = LinkRandPhrase("이제 네 혀를 좀 잘라주마...","네 입만큼 칼 솜씨도 뛰어나길 바란다, 수다쟁이!","자, 이제 네 썩어가는 몸뚱이에 구멍을 몇 개 더 내줄 시간인 것 같군...");
			link.l1.go = "fight";
		break;
		
		case "CaveBanditosTreasure":
			dialog.text = NPCStringReactionRepeat("꺼져, 이봐. 여기서 네가 할 일은 없어!","이봐, 좋게 말할 때 꺼져. 무슨 일이 벌어질지 모른다...","마지막 경고다. 지금 당장 꺼지지 않으면, 여기 온 걸 평생 후회하게 될 거야.","그거야, 이봐. 네가 문제를 자초했지.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("내가 뭘 하든 간섭하지 마, 알았어?","그래서 거기 뭐가 그렇게 특별한데? 그냥 동굴일 뿐이잖아, 별거 없어...","아, 좀 그러지 마...","하! 어디 누가 더 잘하는지 보자, 이 구더기야!",npchar,Dialog.CurrentNode); 
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "CaveBanditosTreasure";
		break;
		
		case "CaveCaribSit":
			if (hrand(2) == 2) 
			{
				dialog.text = NPCStringReactionRepeat("창백한 얼굴, 꺼져라. 그는 기뻐할 거다. "+npchar.name+"  친절하군. 오늘은 신들께서 너를 불쌍히 여기시는 모양이야.","내 형제들이랑 내가 화내기 전에 내 동굴에서 썩 꺼져!","꺼져라, 창백한 놈!","네 운도, 목숨도 끝났어, 하얀 놈아!","block",1,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("그래, 고맙다, 친구야. 참 친절하군...","이 동굴은 네 것이 아니고, 나는 내가 원하는 곳으로 간다.","진정해라, 늪지에서 기어나온 놈아.","이제 네가 한 말을 그대로 네 목구멍에 쑤셔 넣어주마, 짐승아...",npchar,Dialog.CurrentNode); 
				link.l1.go = DialogGoNodeRepeat("exit_talk", "exit", "exit", "fight", npchar, Dialog.CurrentNode);
			}
			else
			{
				dialog.text = LinkRandPhrase("저주받은 창백한 얼굴이 우리 모닥불에 왔군! 우후! 이제 끝장이다!","멍청한 창백이, 네가 재규어의 소굴에 들어왔구나. 네 간을 구워 먹어주마!","건방진 백인이 감히 내 동굴에 들어오다니? 이제 살아서 나가지 못할 거다!");
				link.l1 = LinkRandPhrase("이제 네 혀를 뽑아버리겠다...","이제 세상에 식인종이 좀 줄겠군...","그래, 이제 네 썩어가는 몸뚱이에 구멍 몇 개 더 내줄 때가 된 것 같군, 이 붉은 얼굴 원숭이 자식아.");
				link.l1.go = "fight";
			}
			NextDiag.TempNode = "CaveCaribSit";
		break;
		
		case "CaveCaribStay":
			dialog.text = LinkRandPhrase("더러운 창백한 얼굴이 우리 동굴에 들어왔구나! 흐-히! 네 혀를 잘라내서 튀겨 먹어주마!","멍청한 창백이 놈이 재규어의 소굴에 들어왔구나. 형제들아, 이 저주받은 백인 놈을 베어버려라!","건방진 창백한 얼굴이 내 동굴에 감히 들어오다니? 그럼 살아서 못 나갈 줄 알아!");
			link.l1 = LinkRandPhrase("네 놈 피투성이 머리를 잘라버리겠다...","이제 세상에 식인종이 좀 줄겠군...","좋아, 이제 네 조상들 만나러 갈 준비나 해라, 붉은 피부 녀석. 지옥에나 떨어져라!");
			link.l1.go = "fight";
		break;
		
		case "exit_talk":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_CharacterDisableDialog(sld);
			}
			LAi_CharacterEnableDialog(npchar);
		break;
		
		case "fight":
			DialogExit();
			sGroup = "CaveGroup_" + locations[FindLocation(pchar.location)].index;
			for(i=0; i<4; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "CaveEnc_RaidersAfrer");
			chrDisableReloadToLocation = true;
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
