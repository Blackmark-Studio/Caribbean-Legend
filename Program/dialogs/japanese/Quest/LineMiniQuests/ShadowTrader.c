// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "これはバグだ。開発者に知らせてくれ";
			link.l1 = "もちろんだぜ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "ShadowGuarder":
			dialog.text = "何の用だ？";
			link.l1 = "お前は "+pchar.questTemp.Shadowtrader.Guardername+"？地元の商人が俺を寄越したんだ。あんたの到着を今か今かと待ちわびてるぜ。";
			link.l1.go = "ShadowGuarder_1";
			DelLandQuestMark(npchar);
		break;
	
		case "ShadowGuarder_1":
			dialog.text = "あ、ああ、でも俺はここで彼を待ってたんだ！酒場に来るって聞いてたからな！すまねえ、すぐに向かうぜ。";
			link.l1 = "「よし！」";
			link.l1.go = "ShadowGuarder_2";
		break;
	
		case "ShadowGuarder_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			sld = characterFromId("ShadowGuarder");	
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City +"_store", "goto", "goto2", "OpenTheDoors", 6);
			pchar.questTemp.Shadowtrader = "begin";
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowAgent":
			dialog.text = "こんばんは、船長。安い品でも探してるのかい？ついてきな！";
			link.l1 = "案内してくれ。";
			link.l1.go = "ShadowAgent_1";
		break;
	
		case "ShadowAgent_1":
			DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;
	
		case "ShadowTrader":
			dialog.text = "こんばんは、旦那。新しいお客に会えて嬉しいぜ、はは！自己紹介させてもらうな。俺は "+GetFullName(npchar)+"。俺がこの町で一番安い品を扱ってるんだ、間違いねえぜ。";
			link.l1 = "ついに会えたな……"+npchar.name+"。がっかりさせるかもしれねえが、俺があんたを探してたのは取引のためじゃねえ。 あんたの汚ねえ稼業を終わらせるためだ。あんたはとある大物の尻に大きな痛みを与えてきた。 その痛みがあまりにもひどくなったから、どんな手を使ってでもあんたを潰すつもりでいるんだよ……。";
			link.l1.go = "ShadowTrader_1";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l2 = "そこで止まれ、悪党め！商売をするなら税金を払わなきゃならねえって知らなかったのか？ 俺の目の前で法を破る奴は許さねえぞ！ "+GetFullName(npchar)+"「お前は法を破ったな、盗んだ品はすべて没収だ！この扉の外には武装した兵士が控えているから、 とぼけるんじゃねえぞ！」";
				link.l2.go = "ShadowTrader_2";
			}
			AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;
	
		case "ShadowTrader_1":
			dialog.text = "本当か？思ってもみなかった……てめえ、何者だ！？これは罠じゃねえか！誰の仕業か見当がつくぜ！どうしてもやるしかねえ……野郎ども、ぶっ殺せ！";
			link.l1 = "踊ろうぜ、この野郎！";
			link.l1.go = "ShadowTrader_fight";
			NextDiag.currentnode = "ShadowTrader_6";
		break;
	
	case "ShadowTrader_2":
		dialog.text = "おお神よ……役人さん、聞いてくれ！取引しようぜ。あんたは賢くて情け深い人だ！俺が五千枚のエイトを払うから、 二階から逃がしてくれよ。品物も持っていっていい、必要なんだろ？俺なんか要らないだろ？今すぐ町を出て、 二度と姿を見せねえよ。金も手に入る。どうだ、役人さん？";
		link.l1 = "「おい、クズども、俺がこんなはした金のために自分の義務を汚すと思ってるのか？」";
		link.l1.go = "ShadowTrader_3";
		break;
	
	case "ShadowTrader_3":
		dialog.text = "わかった、わかったよ、役人さん、持ってるもの全部持っていけ――一万ペソだ。これが俺の全財産だ、誓って本当だぜ！";
		link.l1 = "ふん…お前を逮捕すれば、持ってる金は全部没収だ…まあいい！この密輸拠点は閉鎖だ、品物も全部押収する…金をよこして、とっとと失せろ。二度とここに顔を出すんじゃねえぞ！";
		link.l1.go = "ShadowTrader_4";
		break;
		
	case "ShadowTrader_4":
			dialog.text = "ありがとう、ありがとう、ありがとう、旦那！これがあんたの金だ、もう二度とここには来ねえよ。行くぞ！";
			link.l1 = "出て行け、さもないと逮捕するぞ！";
			link.l1.go = "ShadowTrader_escape";
		break;
	
		case "ShadowTrader_fight":
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.nation = PIRATE;
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
	
		case "ShadowTrader_escape"://напугали
			AddMoneyToCharacter(pchar, 10000);
			LAi_SetPlayerType(pchar);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("ShadowAgent_"+i);	
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			}
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 9.0);
			pchar.questTemp.Shadowtrader.End.Escape = "true";
			AddQuestRecord("Shadowtrader", "8");
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 250);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
		break;
	
		case "ShadowTrader_6":
			dialog.text = "ああ！助けてくれ、殺さないでくれ！持ってるものは全部渡すから！";
			link.l1 = "お前の財産はすべて当局に没収されるぞ。ここで起きたことの後で、俺が情けをかけると本気で思ってるのか？";
			link.l1.go = "ShadowTrader_7";
		break;
	
		case "ShadowTrader_7":
			dialog.text = "お、俺の金も持ち物も全部やる！だから見逃してくれ！今日中にこの島を出て、もう二度とここには現れねえ！";
			link.l1 = "よし。持ってる物を全部よこして、とっとと消えな。\n二度とここで商売しようなんて思うなよ――次は命は助けてやらねえぞ、この野郎。";
			link.l1.go = "ShadowTrader_free";
			link.l2 = "冗談じゃねえぞ、この野郎、俺は金で動かねえ。お前みたいな奴には冷たい刃と熱い鉛で応えるしかねえんだ！";
			link.l2.go = "ShadowTrader_killed";
		break;
		
		case "ShadowTrader_free"://отпустили
			AddMoneyToCharacter(pchar, 20550);
			TakeNItems(pchar, "jewelry1", rand(5));
			TakeNItems(pchar, "jewelry2", rand(20));
			TakeNItems(pchar, "jewelry5", rand(20));
			PlaySound("interface\important_item.wav");
			Log_Info("You have received items");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("ShadowTrader"); 
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
			DialogExit();
			DoQuestFunctionDelay("ShadowTrader_final", 7.0);
			pchar.questTemp.Shadowtrader.End.Free = "true";
			AddQuestRecord("Shadowtrader", "9");
			ChangeCharacterComplexReputation(pchar,"nobility", 5); 
			AddComplexSelfExpToScill(70, 70, 70, 70);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
		break;
	
		case "ShadowTrader_killed":
			DialogExit();
			AddDialogExitQuestFunction("ShadowTrader_KillToTrader_kino");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
