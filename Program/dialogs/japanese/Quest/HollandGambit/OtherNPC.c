// диалоги прочих НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "バグだ。開発者に伝えてくれ。";
			link.l1 = "やるぞ！";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (npchar.id == "HWICFernando") NextDiag.CurrentNode = "Fernando";
			DialogExit();
		break;
	
//---------------------------------------за Голландию--------------------------------------------------
		//сопроводить торговца
		case "Baltazar":
			pchar.quest.Create_BaltazarOver.over = "yes";//снять прерывание
			dialog.text = "なんて幸運なんだ！船長、ちょうどフィリップスバーグまで至急護衛が必要なんだ……";
			link.l1 = "お前がバルタザール・リッダーボックか？";
			link.l1.go = "Baltazar_1";
			DelLandQuestMark(npchar);
		break;
		
		case "Baltazar_1":
			dialog.text = "なんだよ、俺はもう総督より有名じゃねえか！お前は誰だ？何の用だ？";
			link.l1 = "私は船長だ "+GetFullName(pchar)+"……ルーカス・ローデンブルクに命じられてあなたのもとに来た。私はあなたとあなたの船を保護する権限を持っている。";
			link.l1.go = "Baltazar_2";			
		break;
		
		case "Baltazar_2":
			dialog.text = "おお、ローデンブルク旦那が私の助けを求める声を聞いてくださったのですね！実は、私掠船がいるのです…";
			link.l1 = "君の話の細かいところは省こう。もう知ってるからな。";
			link.l1.go = "Baltazar_3";			
		break;
		
		case "Baltazar_3":
			dialog.text = "もちろんだ！もう時間を無駄にしすぎた……遅くとも二週間以内にフィリップスバーグへ到着しなきゃならねえ。";
			link.l1 = "それなら自分の船に戻って出航の準備をしろ。すぐに出航するぞ！";
			link.l1.go = "Baltazar_4";			
		break;
		
		case "Baltazar_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 4);
			SetCharacterRemovable(npchar, false);
			npchar.CompanionEnemyEnable = false; //всегда друзья
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.loyality = MAX_LOYALITY;
			AddQuestRecord("Holl_Gambit", "1-3");
			AddMapQuestMarkCity("Marigo", true);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 28, false);
			}
			else SetFunctionTimerCondition("Baltazar_ConvoyOver", 0, 0, 14, false); //таймер
			pchar.quest.BaltazarConvoy_fail.win_condition.l1 = "NPC_Death";//прерывание на потопление сопровождаемого
			pchar.quest.BaltazarConvoy_fail.win_condition.l1.character = "Baltazar";
			pchar.quest.BaltazarConvoy_fail.function = "Baltazar_fail";
			pchar.quest.BaltazarConvoy_complete.win_condition.l1 = "location";//прерывание на выполнение
			pchar.quest.BaltazarConvoy_complete.win_condition.l1.location = "Marigo_town";
			pchar.quest.BaltazarConvoy_complete.function = "Baltazar_complete";
			if (rand(1) == 0)
			{
				BaltazarPirateGlobalCreate();
			}
			else
			{
				pchar.questTemp.HWIC.Holl.BaltazarAttack = "true";
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1 = "location";//прерывание на выполнение
				pchar.quest.BaltazarConvoy_Attack.win_condition.l1.location = "SentMartin";
				pchar.quest.BaltazarConvoy_Attack.function = "BaltazarPirateSeaCreate";
			}
		break;
		
		case "Baltazar_5":
			dialog.text = "ご協力ありがとうございます、船長！あなたの護衛がこれほど絶妙なタイミングで来てくれるとは思いませんでした。 どうか私の感謝と、この5,000ペソをお受け取りください。";
			link.l1 = "ふむ……命を救ったわりには、あまりにも報酬が渋いな……";
			link.l1.go = "Baltazar_6";			
		break;
		
		case "Baltazar_6":
			dialog.text = "それに、機会があればローデンブルク旦那にも手紙を送っておくつもりだ――君の働きを最大限に評価しているとな。では、これで失礼する。";
			link.l1 = "それじゃあ、バルタザール、さらばだ。";
			link.l1.go = "Baltazar_7";			
		break;
		
		case "Baltazar_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 3.0);
			AddQuestRecord("Holl_Gambit", "1-6");
			AddMoneyToCharacter(pchar, 5000);
			ChangeCharacterComplexReputation(pchar,"nobility", 2); 
			ChangeCharacterNationReputation(pchar, HOLLAND, 1);
			ChangeOfficersLoyality("good_all", 1);
			pchar.questTemp.HWIC.Holl = "BaltazarCom";
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		//командировка в Сантьяго
		case "Santiago_Trip":
			dialog.text = "旦那！待って……何か落としたみたいですよ……";
			link.l1 = "何だって？ああ！？";
			link.l1.go = "Santiago_Trip_1";
		break;
		
		case "Santiago_Trip_1":
			DialogExit();
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.FrameLockEsc = true;
			SetLaunchFrameFormParam("You were knocked unconscious from behind", "", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 15, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("SantiagoTripInHouse", 4.0);
		break;
		
		case "Santiago_Trip_2":
			dialog.text = "悪いな、相棒――お前が騒がないように、ちょっとだけ殴らせてもらったぜ。頭がガンガンしてるだろうが、まあ大丈夫だ、 生きてりゃなんとかなるさ。もし時間があれば、な……\n";
			link.l1 = "てめえは誰だ、くそっ、ここで何が起きてやがるんだ？";
			link.l1.go = "Santiago_Trip_3";
		break;
		
		case "Santiago_Trip_3":
			dialog.text = "落ち着け、落ち着け、相棒――また俺がなだめる羽目になるぜ。あの堅物どもが錆びた剣をガチャガチャ鳴らして飛び込んでくるのはごめんだろ？ 静かに話そうじゃねえか。\n";
			link.l1 = "俺の剣を返せ、この野郎、そうしたらちゃんと話してやる、誓うぜ！";
			link.l1.go = "Santiago_Trip_4";
		break;
		
		case "Santiago_Trip_4":
			dialog.text = "お前は素早い小男だな？今のところ剣を抜く必要はねえ。俺の知りたいことを話せば、 もしかしたら無事にここを出られるかもしれねえぞ。わかったか？じゃあ、少し話そうじゃねえか。\n黙ってるのか？いいだろう、交渉成立だ。ローデンブルクから銀行家まで何を運んだ？";
			link.l1 = "「手紙だ。」";
			link.l1.go = "Santiago_Trip_5";
		break;
		
		case "Santiago_Trip_5":
			dialog.text = "賢いな。あれがただの花束じゃないことくらい分かってる。あの手紙には何が書いてあったんだ、坊や？";
			link.l1 = "知るわけないだろ？俺は預かった手紙を読む趣味はねえんだ。\nもしかしたら恋文だったかもな。権力者についてはよく言われるだろ……";
			link.l1.go = "Santiago_Trip_6";
		break;
		
		case "Santiago_Trip_6":
			dialog.text = "…こんな惨めな時代に正直な船長なんて滅多にお目にかかれねえな。\nまあ、お前にとっちゃ悪い知らせだな。あのクソ銀行屋は荷物を受け取ったとき、何て言いやがった？ オランダ人とどんな商売をしてやがるんだ？";
			link.l1 = "フランスから密輸された香水を扱っているんだ……いや、バイエルンの牛糞かもしれないな。";
			link.l1.go = "Santiago_Trip_7";
			link.l2 = "何かの補償についての質問だった。それだけしか知らない。";
			link.l2.go = "Santiago_Trip_8";
		break;
		
		case "Santiago_Trip_7":
			dialog.text = "お前は勇敢な奴だな……しかもユーモアもある。殺すのはもったいねえぜ。ガストンもお前のこと気に入っただろうよ。だが……今はここにいろ。俺はちょっと確かめたいことがあるんでな、ミゲルがその間お前の面倒を見るさ。";
			link.l1 = "誓って言うぜ、「友よ」――お前はこれを後悔することになるぞ！ ";
			link.l1.go = "Santiago_Trip_9";
		break;
		
		case "Santiago_Trip_8":
			dialog.text = "あの傲慢さも消えたな……状況が悪くなると、うちの勇敢な船長も少しは分別を見せるじゃねえか。もっと早くそうしてくれりゃ、 俺たちも手間も時間も省けたのによ。さて、ちょっと確認したいことがあるから出かけるが、戻ったらまた話そう――必要があれば、だがな。しばらくここで待ってろ。俺がいない間はミゲルが面倒見てくれるぜ。\n";
			link.l1 = "誓うぜ、「友よ」――お前はこれを後悔することになる！ ";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_9":
			dialog.text = "もちろんだ。黙っていろよ、“英雄”さん――もしかしたら、まだ何とかなるかもしれないぜ。";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_10":
			dialog.text = "ここで待って、自分の柔軟さが役に立つことを願うんだ。";
			link.l1 = "...";
			link.l1.go = "Santiago_Trip_11";
		break;
		
		case "Santiago_Trip_11":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-44");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Santiago_HouseSp2", "goto", "goto4", "", -1);
			pchar.quest.Santiago_Trip1.win_condition.l1 = "item";
			pchar.quest.Santiago_Trip1.win_condition.l1.item = "slave_01";
			pchar.quest.Santiago_Trip1.function = "SantiagoTrip_wait";
		break;
		
		case "Santiago_Trip_12":
			dialog.text = "なんだと！？";
			link.l1 = "死ぬ覚悟をしろ、このろくでなし！";
			link.l1.go = "Santiago_Trip_13";
		break;
		
		case "Santiago_Trip_13":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitFromRoom");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Santiago_Trip_14":
			dialog.text = "なんてこった！この騒ぎは一体何事かと思っていたんだ。おめでとう――お前はなかなか頭が切れる奴だな！";
			link.l1 = "思ったより頭が切れるな……さて、武装した相手にどこまでやれるか見せてもらおうか！";
			link.l1.go = "Santiago_Trip_15";
		break;
		
		case "Santiago_Trip_15":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "SantiagoTripExitHouse");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//офицер-посланник по 5 заданию
		case "HollQuest_Officer":
			dialog.text = "ルーカス・ローデンブルク旦那がすぐにお前に会いたがっている。今すぐ彼のところへ行け。";
			link.l1 = "向かうところだ。";
			link.l1.go = "HollQuest_Officer_exit";			
		break;
		
		case "HollQuest_Officer_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.HWIC.Holl = "MerdokStart";
			AddQuestRecord("Holl_Gambit", "1-36");
		break;
		
//---------------------------------------------против всех----------------------------------------------
		//убрать испанского идальго
		case "Fernando":
			dialog.text = "俺に何の用だ？";
			link.l1 = "貴様の首だ！";
			link.l1.go = "Fernando_fight";
			link.l2 = "何でもない、気にするな。";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";
		break;
		
		case "Fernando_repeat":
			dialog.text = "またお前か？俺に何の用だ！？説明しろよ！";
			link.l1 = "貴様の首だ！";
			link.l1.go = "Fernando_fight";
			link.l2 = "何でもない、気にするな。";
			link.l2.go = "exit";	
			NextDiag.TempNode = "Fernando_repeat";		
		break;
		
		case "Fernando_fight":
			chrDisableReloadToLocation = true;//выходы закроем
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "SPAIN_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
			pchar.quest.HWIC_Fernando.win_condition.l1 = "NPC_Death";
			pchar.quest.HWIC_Fernando.win_condition.l1.character = "HWICFernando";
			pchar.quest.HWIC_Fernando.function = "Fernando_died";
		break;
		
		//в доме Флитвуда
		case "Fleetwood_soldier"://для любителей сунуть нос куда не надо
			if (CheckAttribute(npchar, "quest.talked"))
			{
			dialog.text = "またお前か？ここで何をうろついているんだ？全く気に入らねえな。よし、 逮捕して司令官の所に連れて行って尋問してやる。野郎ども、こいつを捕まえろ！";
			link.l1 = "でも、俺はただ……";
			link.l1.go = "Fleetwood_soldier_4";	
			}
			else
			{
			dialog.text = "お前は何者だ、何の用だ？説明しろ！";
			link.l1 = "申し訳ありません、旦那、どうやら間違った家に来てしまったようです。お許しください。";
			link.l1.go = "Fleetwood_soldier_1";	
			link.l2 = "リチャード・フリートウッドに会いたい。";
			link.l2.go = "Fleetwood_soldier_2";		
			}
		break;
		
		case "Fleetwood_soldier_1":
			dialog.text = "その通りだ。相手を間違えているぞ。すぐに立ち去ってくれ！";
			link.l1 = "はい。もちろん。";
			link.l1.go = "Fleetwood_soldier_3";			
		break;
		
		case "Fleetwood_soldier_2":
			dialog.text = "本当か？誰がここに住んでいると教えたんだ？怪しいな……よし、お前を逮捕して司令官の執務室に連行する。おい、こいつを捕まえろ！\n";
			link.l1 = "でも、ただリチャードに会いたかっただけなんだ……";
			link.l1.go = "Fleetwood_soldier_4";	
		break;
		
		case "Fleetwood_soldier_3":
			DialogExit();
			npchar.quest.talked = "true";
			DoQuestReloadToLocation("SentJons_town", "reload", "houseSP3", "");
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//для настырных
		break;
		
		case "Fleetwood_soldier_4":
			DialogExit();
			GoToPrison("SentJons", 1000, 10);			
		break;
		
		case "Theft_soldier":
			dialog.text = "あっ！盗賊か？間者か？帽子をしっかり押さえておけよ！";
			link.l1 = "「よっ！」";
			link.l1.go = "Attack_Theft_soldier";			
		break;
		
		case "Attack_Theft_soldier":
			LAi_group_Delete("EnemyFight");
			LAi_SetHP(npchar, 500, 500);
			LAi_SetWarriorType(npchar);
            LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "Attack_soldier":
			dialog.text = "あっ！こいつは何しに来やがったんだ？おい野郎ども、スパイが紛れ込んでやがるぞ！武器を取れ！";
			link.l1 = "「よっ！」";
			link.l1.go = "Attack_soldier_fight";			
		break;
		
		case "Attack_soldier_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//снять запрет драки
			LAi_group_Delete("EnemyFight");
			for (i=1; i<=4; i++)
			{
			sld = characterFromId("Attack_sold_"+i);	
			LAi_SetWarriorType(sld);
            LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareToStreetFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		//Книппель-пленник в трюме
		case "Sailor_deck":
			chrDisableReloadToLocation = true;
			dialog.text = "船長、あんたの指示通りこのろくでなしを尋問したぜ。ちょっと焼きごてを使わせてもらったがな……こいつがこの手紙を持ってやがった。食おうとしたが、止めてやったぜ。やっぱりな、 ウィレムスタッドで女を一人さらって、ボスのところに連れていくつもりだったらしい。";
			link.l1 = "手紙か？見せてくれ。\nそれから私が直接彼に話そう。";
			link.l1.go = "Sailor_deck_1";			
		break;
		
		case "Sailor_deck_1":
			DialogExit();
			AddLandQuestMark(characterFromId("KnippelClone"), "questmarkmain");
			GiveItem2Character(pchar, "NPC_Letter");
			AddQuestRecordInfo("LetterToAbi", "1");
		break;
		
		case "Sailor_deck_2":
			dialog.text = "ご命令は何でしょうか、船長？";
			link.l1 = "死体を海に投げ捨てろ。それから上陸の準備をしろ！";
			link.l1.go = "Sailor_deck_3";			
			// belamour legendary edition -->
			link.l2 = "軍の名誉をもって海に葬ってやれ。あの老人は最後の最後まで勇敢に戦った。砲架から外れた大砲を自分で装填し、 狙いをつけて撃ったんだ。惜しい男だ……別の世界なら、俺たちは戦友になれたかもしれねえな……";
			link.l2.go = "Sailor_deck_3a";
		break;
		
		case "Sailor_deck_3a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			dialog.text = "あいよ、船長！";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_3":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			dialog.text = "了解だぜ、船長！";
			link.l1 = "...";
			link.l1.go = "Sailor_deck_4";			
		break;
		
		case "Sailor_deck_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-21");
			LAi_SetActorType(pchar);
			sld = characterFromId("KnippelClone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("Sailor_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "ReturnMCPlayer", 3);
			}
			pchar.questTemp.HWIC.Self = "toVillemstad";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSP2", "reload2", true);//закроем комнату Аби
		break;
		
		//Лонгвэй-пленник в трюме
		case "Sailor_deck_5":
			chrDisableReloadToLocation = true;
			dialog.text = "ご命令通り、中国人の尋問の準備ができました、船長。奴は何も持っておらず、書類もありませんでした。火鉢を用意し、 手錠と火箸を真っ赤になるまで熱しています。\n";
			link.l1 = "ご苦労だったな、アロンソ。だが始める前に、私から少し説得してみたい。 もしかしたら自分から協力する気になるかもしれんだろう？";
			link.l1.go = "Sailor_deck_6";			
		break;
		
		case "Sailor_deck_6":
			dialog.text = "おっしゃる通りです、船長。";
			link.l1 = "...";
			link.l1.go = "exit";	
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
		break;
		
		case "Sailor_deck_7":
			dialog.text = "はい、船長？";
			link.l1 = "そいつに手錠をかけて、グアドループに着くまで絶対に目を離すな。\nお前たち三人は常にここにいろ。\nもしもの時は命で責任を取ってもらうぞ。";
			link.l1.go = "Sailor_deck_8";			
		break;
		
		case "Sailor_deck_8":
			dialog.text = "了解だぜ、船長！";
			link.l1 = "";
			link.l1.go = "Sailor_deck_9";			
		break;
		
		case "Sailor_deck_9":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Holl_Gambit", "3-48");
			sld = characterFromId("LongwayClone");
			LAi_SetActorType(sld);
			LAi_SetGroundSitType(sld);
			DialogExit();
			pchar.quest.Longway_Shore.win_condition.l1 = "location";
			pchar.quest.Longway_Shore.win_condition.l1.location = "Shore31";
			pchar.quest.Longway_Shore.function = "LongwayInShore";
			AddMapQuestMarkShore("Shore31", true);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		//пьяница - передача письма Флитвуду
		case "Drunkard":
			DelLandQuestMark(npchar);
			dialog.text = "ひっく！こんばんは、旦那！何になさいますか？もしよければ、この酔っ払いに一杯おごってくれませんか？ それから俺は……";
			link.l1 = "聞けよ、この酔っ払いじじい……お前がジャック・ハリソンか？";
			link.l1.go = "Drunkard_1";			
		break;
		
		case "Drunkard_1":
			dialog.text = "おお！はい、それは私です。他に誰がいるっていうんです？なぜです？なーにをしよーうか、よーっぱらいの水夫にぃ～\n";
			link.l1 = "ああ、神よ、どうか私に忍耐をお与えください！\nどの船乗りのことです？あなたの顔を見れば、陸の素人だと一目でわかりますよ……\nお金を稼ぎたいんですか？";
			link.l1.go = "Drunkard_2";			
		break;
		
		case "Drunkard_2":
			dialog.text = "俺はいつだって金を稼ぎたいんだ。どうすりゃいい？\nだが、誰も殺すつもりはねえし、盗みもやらねえ。\nそれに、お前は俺の好みじゃねえ。";
			link.l1 = "誰も殺す必要はないし、お前にそんなことができるとも思えねえ。お前は不器用すぎるからな。\nさあ、これが手紙だ。受け取って総督邸の左隣の家に届けろ。リチャード・フリートウッド宛てだ。";
			link.l1.go = "Drunkard_3";			
		break;
		
		case "Drunkard_3":
			dialog.text = "リチャード・フリートウッドのために？いや……見つかり次第、俺は捕まるぞ。";
			link.l1 = "黙って聞け。誰もお前を逮捕しやしない。アビゲイルの件でチャーリー・クニッペルから来たと言え。 中に通されるはずだ。俺が言ったことを繰り返せ。";
			link.l1.go = "Drunkard_4";			
		break;
		
		case "Drunkard_4":
			dialog.text = "アビゲイルって誰だ？キニッペルなら知ってるが…";
			link.l1 = "お前には関係ねえ。知らない方が長生きできるぜ。さて、待ってるぞ。もう一度言え。";
			link.l1.go = "Drunkard_5";			
		break;
		
		case "Drunkard_5":
			dialog.text = "チャーリー・クニッペルから君の……アビゲイルについて来たんだ。それだけだ。 ";
			link.l1 = "よくやった。この仕事の報酬は五千ペソだ。";
			link.l1.go = "Drunkard_6";			
		break;
		
		case "Drunkard_6":
			if (makeint(Pchar.money) >= 5000)
			{
				dialog.text = "５０００ペソ？おお…手紙を届けるだけで？";
				link.l1 = "いや、別の手紙を渡す。これを酒場に持ってきて、ここに座れ。俺が受け取る。余計なことはするな、怖がる必要もねえ――俺が見張ってるし、すぐそばにいるからな。前金としてこの金をやる、安心しろ。";
				link.l1.go = "Drunkard_7";	
			}
			else
			{
				dialog.text = "五千か？そんな大金、本当に持ってるのか？";
				link.l1 = "はっ！もちろん持ってるぜ。今すぐ持ってくる。";
				link.l1.go = "Drunkard_no_money";	
				NextDiag.CurrentNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_no_money":
			dialog.text = "五千持ってきたか？";
			if (makeint(Pchar.money) >= 5000)
			{
				link.l1 = "はい。どうぞ。心配しないで。";
				link.l1.go = "Drunkard_7";
			}
			else
			{
				link.l1 = "いや、待ってくれ。すぐ戻る。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Drunkard_no_money";
			}
		break;
		
		case "Drunkard_7":
			AddMoneyToCharacter(pchar, -5000);
			RemoveItems(PChar, "MC_Letter", 1);
			dialog.text = "うーん……今行くべきでしょうか、旦那？";
			link.l1 = "いや、木曜の朝……って、今に決まってるだろ、この間抜け！さっさとラムを飲み干して行け！";
			link.l1.go = "Drunkard_8";			
		break;
		
		case "Drunkard_8":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-26");
			LAi_SetStayType(npchar);
			LAi_RemoveLoginTime(npchar);//удалить время загрузки
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "sentjons_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "sentjons_town", "reload", "reload4_back", "DrunkardGoTown", -1);
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("SentJons_town", "reload1_back", true);
			LocatorReloadEnterDisable("SentJons_town", "reload2_back", true);
			LocatorReloadEnterDisable("SentJons_town", "gate_back", true);//чтобы не сбежал
		break;
		
		case "Drunkard_9":
			DelLandQuestMark(npchar);
			dialog.text = "ああ、ここにいらっしゃいましたか、旦那…こんなこと、しなければよかったです。リチャードは読み終えたとたん激怒しました。殺されるかと思いました。";
			link.l1 = "だが、ここにいるじゃねえか！心配すんな――あいつにそんな度胸はねえよ――あの時のお前は、奴にとっちゃあまりにも貴重だったからな、ははっ！どれほどだったか、 お前には想像もつかねえだろうな……";
			link.l1.go = "Drunkard_10";			
		break;
		
		case "Drunkard_10":
			dialog.text = "酒が必要だ……これがあんたへの返事だ。";
			link.l1 = "渡せ！それと黙ってろ！";
			link.l1.go = "Drunkard_11";			
		break;
		
		case "Drunkard_11":
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter1");
			AddQuestRecordInfo("FleetwoodAnswer", "1");
			dialog.text = "ここ数日は話すのが難しいだろう……さようなら……二度と会わないことを願うよ。";
			link.l1 = "気楽にしろよ、この酔っ払いじじい、ははは！酔っ払い水夫をどうしようか～♪\n飲んでくつろげ、もう全部終わったんだからな！";
			link.l1.go = "Drunkard_12";			
		break;
		
		case "Drunkard_12":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-27");
			pchar.questTemp.HWIC.Self = "FleetwoodAgree";
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		//кэп курьерского судна
		case "Cureer_abordage":
			dialog.text = "「なんで俺の船を襲ったんだよ！？財宝も金もねえし、あるのは書類だけだが、お前らには何の役にも立たねえだろうが！ 」";
			link.l1 = "黙れ。お前は負けたんだ、これからは俺の話を聞け。俺はお前の船も書類もいらねえ。お前に必要なのは、 この伝言をお前のボス、あの汚いネズミ野郎ルーカス・ローデンブルクに届けることだ。 フリートウッド船長からの挨拶だと伝えろ。";
			link.l1.go = "Cureer_abordage_1";			
		break;
		
		case "Cureer_abordage_1":
			dialog.text = "フリートウッド船長？しかし…";
			link.l1 = "この手紙をお前の上司に渡すか――それとも俺がここでお前を斬るか？配達役なら他にも探せるぜ。 退屈しのぎに毎週お前ら汚ねえ会社の船を襲ってるってこと、覚えとけよ。\n";
			link.l1.go = "Cureer_abordage_2";			
		break;
		
		case "Cureer_abordage_2":
			dialog.text = "わかりました、フリートウッド旦那。お届けします。";
			link.l1 = "それは素晴らしいことだ。これでお互いに別れを告げられるな、旦那。今日は自分がとても運が良かったと思うんだな。 そして、到着したら教会に寄るのを忘れるなよ！";
			link.l1.go = "Cureer_abordage_3";			
		break;
		
		case "Cureer_abordage_3":
			DialogExit();
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			pchar.quest.HWICCureer_AfterBattle.over = "yes";
			pchar.quest.HWICCureerOnMapOver.over = "yes";
			AddQuestRecord("Holl_Gambit", "3-39");
			Log_TestInfo("THE LETTER HAS BEEN DELIVERED!");
			RemoveItems(PChar, "MC_Letter", 1);
			pchar.questTemp.HWIC.Self = "LetterToLucasSent";
			pchar.quest.Curacao_exploring.win_condition.l1 = "location";
			pchar.quest.Curacao_exploring.win_condition.l1.location = "Curacao";
			pchar.quest.Curacao_exploring.function = "CuracaoExploring";
			DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
			AddComplexSeaExpToScill(50, 50, 50, 100, 50, 50, 0);
			AddComplexSelfExpToScill(30, 30, 30, 30);
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		//Матиас Бек в тюрьме
		case "MatiasBek"://на случай если геймер захочет пообщаться
			dialog.text = "俺は不当逮捕されたんだ！イギリス人なんかと関係ねえ！全部ローデンブルクの陰謀だ。まあいいさ。 すぐにピーター・スタイフェサントが来る――あいつが全部片付けてくれるさ！";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "MatiasBek";
		break;
		
		//стражник у входа в резиденцию
		case "QuestGuard":
			dialog.text = "ルーカス・ローデンブルク旦那は只今どなたにもお会いになりたくありません。\nどうかすぐに屋敷をお立ち退きください。";
			link.l1 = "ふむ。なるほど。一週間後に立ち寄ってみるよ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "QuestGuard";		
		break;
		
		//Питер Стайвесант
		case "Stivesant":
			dialog.text = "邸宅へ向かいます、船長。すでに部下を砦に送り、マティアス・ベックの情報を集めさせています。 もし本当に今牢獄にいるなら、もう釈放されて町に連れて来られているはずです。ついてきてください！";
			link.l1 = "はい、スタイフェサント旦那。";
			link.l1.go = "Stivesant_1";			
		break;
		
		case "Stivesant_1":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Villemstad_townhall", "goto", "goto2", "OpenVillemstadResidence", -1);
		break;
		
		case "ArestLucas_1":
			dialog.text = "ルーカス！ここで何が起きているんだ？マティアス・ベックはどこだ？本当に彼を牢屋に送ったのか？";
			link.l1 = "";
			link.l1.go = "ArestLucas_2";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_2":
			StartInstantDialog("Lucas", "ArestLucas_3", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_3":
			dialog.text = "やあ、スタイフェサント旦那。奴がイギリス諜報部、しかもフリートウッド船長と直接繋がっている証拠を手に入れたぜ。 あの野郎、我々の運送用ブリガンティンを襲撃して、会社の機密書簡を奪うよう、あの忌々 しいイギリス人に密告しやがったんだ。";
			link.l1 = "";
			link.l1.go = "ArestLucas_4";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_4":
			StartInstantDialog("Stivesant", "ArestLucas_5", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_5":
			dialog.text = "「この情報はどこで手に入れたんだ？」";
			link.l1 = "";
			link.l1.go = "ArestLucas_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_6":
			StartInstantDialog("Lucas", "ArestLucas_7", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_7":
			dialog.text = "それは通報用ブリガンティンの船長が主張していた。リチャード・フリートウッドがその船に乗り込み、 書類を持ち去った後、船は解放された。航路や予定について知っていたのは、私と君、 そしてマティアス・ベックだけだった。\n";
			link.l1 = "";
			link.l1.go = "ArestLucas_8";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));
		break;
		
		case "ArestLucas_8":
			StartInstantDialog("Stivesant", "ArestLucas_9", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_9":
			dialog.text = "「だからベックがフリートウッドにブリガンティン襲撃を密告したと決めつけたのか？馬鹿げてる！ フリートウッドはただの海賊で、商船しか襲わないんだ。そもそも帳簿の情報しか入っていない書類なんて、 あいつに何の用がある？」";
			link.l1 = "";
			link.l1.go = "ArestLucas_10";		
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_10":
			StartInstantDialog("Lucas", "ArestLucas_11", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_11":
			dialog.text = "旦那、あの使者は通常の報告書だけでなく、他にも重要な会社の書類を運んでいたのです。そして今、 それらはすべてイギリス人の手に渡ってしまいました。だからこそ、私はベックを逮捕することに決めたのです。";
			link.l1 = "";
			link.l1.go = "ArestLucas_12";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_12":
			StartInstantDialog("Stivesant", "ArestLucas_13", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_13":
			dialog.text = "くそっ！これはまさに権力の簒奪だ！ルーカス、お前は自分が何をしているのか本当に分かっているのか？\n通報用ブリガンティンの船長はどこだ？";
			link.l1 = "";
			link.l1.go = "ArestLucas_14";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			LAi_ActorAnimation(npchar, "dialog_stay13", "1", 4.5);
		break;
		
		case "ArestLucas_14":
			StartInstantDialog("Lucas", "ArestLucas_15", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_15":
			dialog.text = "「フィリップスバーグへ行きましたぜ、旦那。」";
			link.l1 = "";
			link.l1.go = "ArestLucas_16";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_16":
			StartInstantDialog("Stivesant", "ArestLucas_17", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_17":
			dialog.text = "よろしい、それなら。ベックの釈放を命じておいた。ここに連れて来させるから、三人で話をしよう。";
			link.l1 = "";
			link.l1.go = "ArestLucas_18";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_18":
			StartInstantDialog("Lucas", "ArestLucas_19", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_19":
			dialog.text = "よし、俺は構わねえ。三人でいいぜ。話そうじゃねえか。";
			link.l1 = "";
			link.l1.go = "ArestLucas_20";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));	
		break;
		
		case "ArestLucas_20":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "governor1", "DoubleTalkWithLucas", -1.0);
			locCameraFromToPos(4.70, 2.92, -4.19, false, 3.60, -0.70, 5.00);
			DoQuestCheckDelay("PiterTalkWithLucas_2", 4.5);
		break;
		
		case "ArestLucas_40":
			dialog.text = "お前の無法の報いを受けるがいい、ローデンブルク！お前の告発は馬鹿げている。 ブリガンティンの船長に会うことすら許されなかったじゃないか！証拠も何も出していないし、 すべての非難はお前個人からのものだ。\n神に誓って、俺は無実だ！イギリス人とは今までもこれからも一切関わりはない！";
			link.l1 = "";
			link.l1.go = "ArestLucas_41";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
		break;
		
		case "ArestLucas_41":
			StartInstantDialog("Lucas", "ArestLucas_42", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_42":
			dialog.text = "へえ、本当かい？じゃあ、どうしてフリートウッドが俺たちのブリガンティンと、 あの船に普通の書類以上のものが積まれてたって知ったんだ？";
			link.l1 = "";
			link.l1.go = "ArestLucas_43";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Villemstad_Mayor"));
		break;
		
		case "ArestLucas_43":
			dialog.text = "...";
			link.l1 = "ローデンブルクは嘘をついている。リチャード・フリートウッドが通報用ブリガンティンを襲ったはずがない。";
			link.l1.go = "ArestLucas_44";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			sld = characterFromId("Stivesant");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = characterFromId("Villemstad_Mayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "ArestLucas_44":
			dialog.text = "「で、あんたは誰だ、マインヘール？何の権利があってそんなことを言ってるんだ？」";
			link.l1 = "私の名前は "+GetFullName(pchar)+"。俺が個人的にフリートウッド船長を罠に誘い込んで始末した。奴の死体はタークスの海岸でカモメの餌になっている。 役人どもは俺たちオランダ商人を奴の暴力から守れなかったから、俺が自分でケリをつけたのさ。そして、 それは急使のブリガンティンが略奪される前のことだったんだ…";
			link.l1.go = "ArestLucas_46";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
		break;
		
		case "ArestLucas_46":
			dialog.text = "";
			link.l1 = "フリートウッドには到底できなかった、彼はすでに死んでいたのだから。酒場で地元の人々 からマティアス・ベックが逮捕されたと聞き、この件を調べることにした。なぜなら、 私は昔からベック旦那が潔白な評判の持ち主だと信じていたからだ…";
			link.l1.go = "ArestLucas_47";			
		break;
		
		case "ArestLucas_47":
			dialog.text = "";
			link.l1 = "港の連中が言っていたぞ。お前は自分のシーベックにあらゆる犯罪者や傭兵どもを乗せ、 会社の衛兵たちは岸に残したそうだな。俺はお前の船を追い、捕らえた。雇った悪党どもは一人残らず斬り捨てたぜ。 ロングウェイ船長を尋問し、自由と引き換えに全てを話させたんだ、ローデンブルク旦那……";
			link.l1.go = "ArestLucas_48";			
		break;
		
		case "ArestLucas_48":
			dialog.text = "";
			link.l1 = "お前はキュラソーの支配権を奪おうと企み、ロンウェイにスタイフェサント旦那のガレオンを沈めるよう命じたんだろう。 お前のやり口を知っていれば、あのブリガンティンの哀れな船長はもう死んでいるに違いない。 前例を作るために使者船への襲撃もお前が仕組んだはずだ、違うか？そしてその実行犯はお前の刺客、 ヤーコプ・ファン・ベルクだったのか？ロンウェイがあの男について色々話してくれたぞ。";
			link.l1.go = "ArestLucas_49";			
		break;
		
		case "ArestLucas_49":
			dialog.text = "こ、これは明らかな嘘だ！何を言っているんだ、旦那？お前はいったい何者だ！？";
			link.l1 = "俺は独立した船長だ。あの悪党フリートウッドを海と陸から追い払いたかっただけなのに、 あんたらの政治的な陰謀に巻き込まれちまった！スタイフェサント旦那には危険を警告しておいたぜ。今ここにいるのは、 合法の当局と共に、あんたのキュラソーでの略奪行為に終止符を打つためだ！";
			link.l1.go = "ArestLucas_50";			
		break;
		
		case "ArestLucas_50":
			dialog.text = "なんという無礼だ！お前の言葉の責任は取ってもらうぞ、マインヘール“独立船長”！貴様……";
			link.l1 = "";
			link.l1.go = "ArestLucas_51";
		break;
		
		case "ArestLucas_51":
			StartInstantDialog("Stivesant", "ArestLucas_52", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_52":
			dialog.text = "もういい、ルーカス。お前の罪は必ず償わせる！十分に聞いたし、見てもきた。ルーカス・ローデンブルク、 貴様を逮捕する。会社の総監の命を狙ったこと、武力で権力を奪おうとしたこと、そして連絡船の船長殺害の容疑でな。\nさらに、公式な捜査の中でお前の経歴の興味深い部分も明らかになるだろう。拘束してアムステルダムへ連行し、 裁判にかける。連れて行け！";
			link.l1 = "";
			link.l1.go = "ArestLucas_53";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Stivesant"));					
		break;
		
		case "ArestLucas_53":
			StartInstantDialog("Lucas", "ArestLucas_54", "Quest\HollandGambit\OtherNPC.c");
		break;
		
		case "ArestLucas_54":
			dialog.text = "しかし……";
			link.l1 = "";
			link.l1.go = "ArestLucas_55";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, characterFromID("Stivesant"));			
		break;
		
		case "ArestLucas_55":
			DialogExit();
			LAi_ActorTurnToCharacter(pchar, characterFromID("Lucas"));
			sld = characterFromId("Lucas");
			LAi_SetImmortal(sld, true);//защита от хитреца
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "LucasGoToPrison", -1);
			for (i=3; i<=5; i++)
			{
			sld = characterFromId("StivesantGuard_"+i);
			LAi_ActorFollow(sld, characterFromID("Lucas"), "", -1);
			}
			LAi_SetActorType(PChar);
			locCameraFromToPos(4.70, 2.92, -4.19, false, -4.60, -1.70, 5.50);
			DoQuestFunctionDelay("SecondDayInVillemstad", 6.0);
		break;
		
		case "Stivesant_10":
			dialog.text = "Captain "+GetFullName(pchar)+"！ウィレムスタッド植民地行政を代表して、あなたの行動によりあの危険な犯罪者を逮捕できたこと、 心より感謝申し上げます。\nまた、私自身も命を救われたかもしれず、個人的にもお礼を申し上げたいと思います。";
			link.l1 = "私は全てのオランダ植民地のために行動したのです、旦那。";
			link.l1.go = "Stivesant_11";			
		break;
		
		case "Stivesant_11":
			dialog.text = "君の謙虚さには敬意を表するよ、友よ。さて、いくつか形式的なことを片付けたい。 君がメイフェン号を善意と切羽詰まった状況で拿捕した以上、何の異議もない。しかし、この船は会社の所有物だから、 返却をお願いしたいんだ。";
			link.l1 = "かしこまりました、旦那。";
			link.l1.go = "Stivesant_12";			
		break;
		
		case "Stivesant_12":
		//удаляем Мейфенг
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
		if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
		{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "A boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
		}
		else
		{
			for(i = 1; i < COMPANION_MAX; i++)
			{
			int iTemp = GetCompanionIndex(PChar, i);
			if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
					{
						pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
						sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
						RemoveCharacterCompanion(PChar, sld);
						AddPassenger(PChar, sld, false);
					}
				}
			}
		}
			dialog.text = "明日、私の邸宅へお越しください――あなたの功績を称え、自由州共和国を代表して表彰いたします。どうか町を離れずにいてくださいますよう、 お願い申し上げます。";
			link.l1 = "わかりました、旦那。明日また伺います。";
			link.l1.go = "Stivesant_13";			
		break;
		
		case "Stivesant_13":
			DialogExit();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.dialog.currentnode = "Bek_2";
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;
		
		case "Bek_2":
			dialog.text = "私からも個人的にお礼を申し上げたい、船長。あなたの進取の気性と迅速な助力には感謝している。\n明日もここに来るのを忘れないでくれ、あなたのために貴重な贈り物を用意しておく。";
			link.l1 = "ありがとうございます、ベック旦那。必ず参ります！";
			link.l1.go = "Bek_3";			
		break;
		
		case "Bek_3":
			DialogExit();
			pchar.quest.Award_FromPiter.win_condition.l1 = "Timer";
			pchar.quest.Award_FromPiter.win_condition.l1.date.hour  = 9.0;
			pchar.quest.Award_FromPiter.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromPiter.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromPiter.function = "OpenResidenceDoor";
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload5_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload10_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);//закрыть вход в резиденцию
			LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);//закрыть боковой вход в резиденцию
			AddQuestRecord("Holl_Gambit", "3-53");
			DoQuestReloadToLocation("Villemstad_prison", "goto", "goto23", "TalkWithLucasPrisoner");
			for (i=4; i<=5; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
		break;
		
		case "Stivesant_14":
			dialog.text = ""+GetFullName(pchar)+"「自由州共和国を代表して、 全てのオランダ人の敵であり国家犯罪者リチャード・フリートウッドの排除におけるあなたの主導的な働きに対し、 ここに個人用武器と十万ペソを授与する。おめでとう！」";
			link.l1 = "ありがとうございます、スタイフェサント旦那！";
			link.l1.go = "Stivesant_15";			
		break;
		
		case "Stivesant_15":
			dialog.text = "さらに、前例のない勇気、会社内の裏切りの陰謀を暴いた功績、そして元副社長を大胆に捕らえたことにより、 あなたには十五万ペソが授与される。また、オランダ西インド会社との契約も許可されるだろう\n新しい副社長が、あなたのような勇敢な船長にふさわしい高給の職をきっと用意してくれるはずだ。";
			link.l1 = "ありがとうございます！心に留めておきます。";
			link.l1.go = "Stivesant_16";			
		break;
		
		case "Stivesant_16":
			AddMoneyToCharacter(pchar, 250000);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			dialog.text = "オランダの側に立ち、オランダの利益のために行動する限り、私の助力はいつでも頼りにしてくれて構わない。\nさて、ウィレムスタッド総督マティアス・ベックの話を聞こうじゃないか。";
			link.l1 = "";
			link.l1.go = "Stivesant_17";			
		break;
		
		case "Stivesant_17":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "Bek_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);		
		break;
		
		case "Bek_4":
			dialog.text = "心から感謝申し上げます、船長。国家への陰謀を見抜いたあなたの勇気と洞察力に敬意を表します。 こちらの貴重な航海用計器を贈呈いたします。軍艦乗りには欠かせない品でございます。";
			link.l1 = "ありがとうございます、ベック旦那";
			link.l1.go = "Bek_5";			
		break;
		
		case "Bek_5":
			GiveItem2Character(pchar, "bussol");
			dialog.text = "知っておいてほしい。今やあなたは私の友人であり、それは私にとって大きな意味がある。\n私の邸宅には、いつでも歓迎する客人として迎えるつもりだ。\nどんな理由でも、いつでも立ち寄ってくれれば嬉しい。必要な助けがあれば、喜んで力になるよ。";
			link.l1 = "それを聞いて嬉しいぜ、旦那！";
			link.l1.go = "Bek_6";			
		break;
		
		case "Bek_6"://наведем порядок в городе
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-54");
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetHuberStayType(sld);
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("StivesantGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Stivesant");
			LAi_ActorGoToLocator(sld, "goto", "goto6", "StivesantSitDown", -1);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			DelMapQuestMarkCity("Villemstad");
		break;
		
		case "Bek_7":
			dialog.text = "オランダはあなたを誇りに思っています、旦那。あなたのような船長こそがカリブ海のオランダ艦隊の支えです。さあ、 どうぞ、報酬をお受け取りください。";
			link.l1 = "ありがとうございます、旦那。オランダに仕えることを光栄に思います！";
			link.l1.go = "Bek_8";
		break;
		
		case "Bek_8":
			TakeNItems(pchar, "gold_dublon", 1000);
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			ChangeCharacterNationReputation(pchar, HOLLAND, 20);
			DialogExit();
			sld = characterFromId("Lucas");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "LucasAward_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Stivesant_18":
			dialog.text = "お会いできて嬉しいです。お元気ですか？";
			link.l1 = "私は元気です。ちょっとあなたに会いに立ち寄っただけです。";
			link.l1.go = "exit";	
			NextDiag.TempNode = "Stivesant_18";
		break;
		
		// Jason НСО
		case "Stivesant_19":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "誰かと思えば！それは "+GetFullName(pchar)+"。最近、俺たちの用心棒を使ってお前をここに連れて来させたんだ。その手間もずいぶん金がかかったぜ。";
				link.l1 = "うーん……行かなくちゃ……";
				link.l1.go = "arest";
				break;
			}
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (pchar.questTemp.Patria == "epizode_4" && IsUniformEquip())
			{
				dialog.text = "フランス海軍の船長か？よし、時間がないが、話は聞こう。何の用でここに来た？";
				link.l1 = "スタイフェサント旦那、私はサン・クリストファーからフランス領植民地総督ポワンシー騎士の伝言を持って参りました。 ";
				link.l1.go = "Stivesant_20";
			}
			else
			{
				dialog.text = "失礼します、船長。ただいま非常に忙しくて、あなたに割ける時間がありません。マティアス・ベック旦那に話しかけて、 あなたの言い分を聞いてもらってください。";
				link.l1 = "ふむ……";
				link.l1.go = "Stivesant_19_1";
			}
		break;
		
		case "Stivesant_19_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
		break;
		
		case "Stivesant_20":
			sld = characterFromId("Patria_FlautCap");
			dialog.text = "ポワンシー騎士からか？まさかこんなに簡単に済むとは思わなかったよ…ゴホン…で、騎士殿のご様子はどうだ？";
			link.l1 = "すべて順調でございます、旦那。ポワンシー様からこの手紙をお届けするよう命じられました。 もう一つの任務は護衛でございます\n "+sld.ship.name+"「おたくの会社向けの貨物を積んでウィレムスタッド港まで運んできた船だ。船は埠頭に停泊していて、貨物も無傷だ。」 ";
			link.l1.go = "Stivesant_21";
		break;
		
		case "Stivesant_21":
			dialog.text = "我が社向けの積荷を積んだ艦隊か？面白いな……で、その手紙はどうした、船長？";
			link.l1 = "どうぞ。これを受け取ってください。";
			link.l1.go = "Stivesant_22";
		break;
		
		case "Stivesant_22":
			RemoveItems(pchar, "Reserve_item_01", 1);
			dialog.text = "ふむ……（読みながら）。本国からの査察か……ゴホン……ほう、これは……面白いな、ふふ……ところで、船長、カリブでフランスがスペインと戦争中だって聞いたが？サンホセ要塞の包囲と略奪、 キューバ東岸沖でのスペイン艦隊の壊滅……";
			link.l1 = "イスパニョーラ島西岸、ポルトープランスの近くだ、旦那。サン・ホセ包囲の唯一の目的は、サン＝ ピエール襲撃に対する賠償金をスペイン人から取ることだったんだ。うちはスペインとはずっと仲が悪いからな……いつ返答をもらいに戻ればいい？";
			link.l1.go = "Stivesant_23";
		break;
		
		case "Stivesant_23":
			dialog.text = "お引き止めはしませんよ、船長。あなたは軍人ですから、きっと多忙でしょうし、 シュヴァリエ殿もあなたの帰りを心待ちにしているはずです。どうかご親切に、 ここ応接間で二時間ほどお待ちいただけますか。その間にあの手紙への返事を書かせていただきます。 どうぞお掛けになってお休みください。ご希望でしたらワインかラム酒をお持ちします……\n";
			link.l1 = "感謝するぜ、旦那。でも俺は上等なワインを一杯いただきたいんだが…";
			link.l1.go = "Stivesant_24";
		break;
		
		case "Stivesant_24":
			chrDisableReloadToLocation = true;//закрыть локацию
			pchar.quest.Patria_CureerTimeOver.over = "yes"; //снять таймер
			pchar.quest.Patria_CureerFail.over = "yes"; //снять прерывание
			sld = characterFromId("Patria_FlautCap");
			RemoveCharacterCompanion(pchar, sld);
			sld.lifeday = 0;
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_25";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Villemstad_townhall", "goto", "goto6");
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "Patria_StivesantWait", -1);
			pchar.questTemp.Patria = "epizode_4_return";
		break;
		
		case "Stivesant_25":
			GiveItem2Character(pchar, "Reserve_item_01");
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_2");
			dialog.text = "ポワンシー様への返答は用意できました。どうぞ、お受け取りください…ご武運を、船長。";
			link.l1 = "ありがとうございます、旦那。ごきげんよう！";
			link.l1.go = "Stivesant_26";
		break;
		
		case "Stivesant_26":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_19";
			chrDisableReloadToLocation = false;
			AddQuestRecord("Patria", "23");
			SetFunctionTimerCondition("Patria_CureerBackOver", 0, 0, 31, false);
		break;
		
		case "Stivesant_27":
			if (ChangeCharacterHunterScore(pchar, "holhunter", 0) > 10)
			{
				dialog.text = "誰かと思えば！こいつは "+GetFullName(pchar)+"……最近、我々はお前をここに連れてくるために腕利きの連中を送り込んだんだ。その手間もかなり金がかかったぞ。";
				link.l1 = "うーん…行かなくちゃ…";
				link.l1.go = "arest";
				break;
			}
			if (pchar.questTemp.Patria == "epizode_6" && IsUniformEquip())
			{
				dialog.text = "また総督フィリップ・ド・ポワンシーからの伝言を持って来たんだな？";
				link.l1 = "はい、スタイフェサント旦那。シント・マールテンの岸で不幸な誤解がありまして……パリから来た監察官、ノエル・フォルジェ男爵を乗せた船がフィリップスブルフの砦から砲撃されてしまい、それで……\n";
				link.l1.go = "Stivesant_28";
			}
			else
			{
				dialog.text = "失礼します、船長。ただ今非常に忙しくて、あなたに割く時間がありません。マティアス・ベック旦那に話しかけて、 あなたの話を聞いてもらってください。";
				link.l1 = "ふむ……";
				link.l1.go = "Stivesant_27_1";
			}
		break;
		
		case "Stivesant_27_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_27";
		break;
		
		case "Stivesant_28":
			if (pchar.questTemp.HWIC.Detector == "holl_win" || pchar.questTemp.HWIC.Detector == "self_win")
			{
				dialog.text = "だからこそ、あんたがここにいるんだ、船長。俺は外交の話なんかしないぜ。シュヴァリエにはこう伝えてくれ――もはやシント・マールテンの支配者じゃねえってな。もう奴は十分だ。それと、本国からの査察については……奴自身で何とか言い訳を考えさせろ。デ・ポワンシーなら、何だってひっくり返すのは昔から朝飯前だったろうよ。";
				link.l1 = "「それをそのまま彼に伝えればいいのか？」";
				link.l1.go = "Stivesant_29";
			}
			else
			{
				dialog.text = "だからこそ、あなたがここにいるのですよ、船長。私は外交的な議論をするつもりはありません。 あなたの主君は最近シント・マールテンであまりにも強欲に振る舞いましたので、 その飽くなき欲望を抑える時が来たのです。そして、主君もそのことを十分に理解しているはずです。さて、 シャルル・ド・モール船長、あなたについても、 リチャード・フリートウッドという名のイギリス人盗賊に関する最近の出来事について質問がありますので、 しばらくここに留まってもらいます。\n軍曹！船長の武器を取り上げ、司令官の執務室へ連れて行け！";
				link.l1 = "任務中のフランス士官を遅らせるとは許されないぞ！";
				link.l1.go = "Stivesant_31";
			}
		break;
		
		case "Stivesant_29":
			dialog.text = "俺もまったく同感だぜ、船長。あんたの上官ならすべて理解するだろうが、あんたが深入りする必要はねえ、 どうせ何も変わらねえからな。幸運を祈るぜ。\n軍曹、シャルル・ド・モール旦那を出口まで案内してくれ！";
			link.l1 = "...";
			link.l1.go = "Stivesant_30";
		break;
		
		case "Stivesant_30":
			DialogExit();
			DoQuestReloadToLocation("Villemstad_town", "reload", "reload3", "Patria_DiplomatGetOut");
		break;
		
		case "Stivesant_31":
			dialog.text = "残念だが、私の考えは違う。軍曹！もし抵抗するなら、力を使え！";
			link.l1 = "お前はまだ自分が誰と関わっているのか分かってねえんだよ、旦那・・・";
			link.l1.go = "Stivesant_32";
		break;
		
		case "Stivesant_32":
			DialogExit();
			Patria_DiplomatFight();
		break;
		
		case "Stivesant_33":
			dialog.text = "この役割でお前を見るのは少し奇妙だな、シャルル・ド・モール船長…。交渉のためにお前のもとへ来る者たちに免責を保証できると願いたいものだ…。";
			link.l1 = "それは間違いありませんぜ、スタイフェサント旦那。";
			link.l1.go = "Stivesant_34";
		break;
		
		case "Stivesant_34":
			dialog.text = "それでは、あなたが用意した契約書を読ませていただけませんか？\nお手紙の内容が含まれていると理解しておりますが。";
			link.l1 = "その通りだ、旦那。ただし正式な形でな。フランス側からは――関係の中立への回復、シント・マールテン島へのいかなる権利主張の放棄。イングランド側からは――貿易戦争の終結。詳細はすべてここに記されている……そしてもちろん、そちらが始めた軍事行動によって我々が被った損害への金銭的補償も含まれる。";
			link.l1.go = "Stivesant_35";
		break;
		
		case "Stivesant_35":
			dialog.text = "どうかその書類を私にお渡しください。";
			link.l1 = "もちろんです。";
			link.l1.go = "Stivesant_36";
		break;
		
		case "Stivesant_36":
			dialog.text = "……（朗読中）……";
			link.l1 = "...";
			link.l1.go = "Stivesant_37";
		break;
		
		case "Stivesant_37":
			LAi_Fade("", "");
			dialog.text = "選択の余地がなかったので、この協定に署名しよう。しかし、 私にとってウィレムスタッドとその住民の保護が最も重要なのだ\n";
			link.l1 = "では、三通すべてに署名して正式に認証しましょう。 私はフランス側としてフィリップ・ド・ポワンシー総督の権限でこの書類に署名します。 イングランド側はドイリー大佐が署名します。";
			link.l1.go = "Stivesant_38";
		break;
		
		case "Stivesant_38":
			dialog.text = "…（署名中）…";
			link.l1 = "完璧だ！さて、これに署名しよう…";
			link.l1.go = "Stivesant_39";
		break;
		
		case "Stivesant_39":
			LAi_Fade("", "");
			dialog.text = "それで、包囲を解いてくれるんだろうな？";
			link.l1 = "間違いありません。協定のすべての条件がオランダ側によって違反なく守られることを願っています。";
			link.l1.go = "Stivesant_40";
		break;
		
		case "Stivesant_40":
			dialog.text = "イングランドやフランスによる違反がなければ、我々は契約の条件を守るつもりだ、だから心配するな。";
			link.l1 = "戦うよりも取引した方がいつだって賢明ですよ、スタイフェサント旦那。\nこれで安心してウィレムスタッドへお戻りになれます。包囲は解かれ、我々 の戦隊もまもなくキュラソーの海域を離れます。";
			link.l1.go = "Stivesant_41";
		break;
		
		case "Stivesant_41":
			DialogExit(); // Стайвесант уходит, подходит д'Ойли
			Patria_CuracaoStivesantGo();
		break;
		
		case "Stivesant_42":
			dialog.text = "それで、あなたがノエル・フォルジェ男爵か？ほう、そしてあなたがシャルル・ド・モール旦那ご本人だな！ ご挨拶申し上げます、副提督殿！諸島一の策士と呼ばれる理由がよく分かる――あなたが今どちらの味方なのか、誰にも分からないんですからね……\n";
			link.l1 = "副提督は国王陛下の側におり、そして今この瞬間、私もその正当な代理人としてあなたの味方でございます。";
			link.l1.go = "Stivesant_43";
		break;
		
		case "Stivesant_43":
			dialog.text = "王はここから遠く離れておりますし、フランスも同様です、バロン。しかし、 聖クリストフとシュヴァリエ・ド・ポアンシーはすぐ近くにおります。彼こそがフランス領植民地の実質的な支配者です。 事実上……。\nですが、あなたは財務大臣の目にポアンシーを不利にするような何かを手に入れるためにここに来たのですか？";
			link.l1 = "その通りだ、旦那。";
			link.l1.go = "Stivesant_44";
		break;
		
		case "Stivesant_44":
			dialog.text = "私の手元にそのような書類がある。これは鉱山やその他の件に関する私とド・ポワンシーの帳簿全体だ。中には、 この事業に関する大量の書類も入っていて、そのすべてにフィリップ・ド・ポワンシーの直筆の署名がある。断言するが、 これらの書類の内容は、興味を持つ者の手に渡れば、 シュヴァリエをカリブ海の底よりもさらに深く沈めることになるだろう。";
			link.l1 = "この台帳に何が欲しいんだ？";
			link.l1.go = "Stivesant_45";
		break;
		
		case "Stivesant_45":
			dialog.text = "ただ同然で売ってやるよ。たった銀貨百万ペソさ。";
			link.l1 = "百万ペソだと？！！";
			link.l1.go = "Stivesant_46";
		break;
		
		case "Stivesant_46":
			dialog.text = "その通りです、男爵。この金額で、最近の戦争による損失の一部は少なくとも補填できるでしょう。 一つ助言を差し上げます。シャルル・ド・モール旦那に頼ってみてはいかがでしょう。ド・ポワンシー殿や、ええと……他の方々のために働いていた間に、彼はきっと莫大な財産を築いたはずですし、百万くらい簡単に用意できるでしょう。 私はほぼ確信しています。\n期限をお伝えします――一ヶ月です。この期間内に指定した金額を持参できなければ、シュヴァリエ殿に書簡を送り、 あなたが私を訪ねてきた経緯を詳しく説明します。その後どうなるかは、ご想像にお任せします。";
			link.l1 = "俺を脅してるのか！植民地で百万なんて、とても用意できるはずがないって分かってるだろう！";
			link.l1.go = "Stivesant_47";
		break;
		
		case "Stivesant_47":
			dialog.text = "もちろん理解しています。だからこそ、すぐにこの百万を持つ人物をあなたに示したのです。 もしド・モール旦那が断れば、バロン、 あなたはシュヴァリエが私の手紙を受け取る前にヨーロッパへ出航した方がいいでしょう。さもないと、 ここに永遠に留まることになるかもしれません。ド・モール旦那については……もちろん提督の地位は失いますが、脱出はできるでしょう……それに、彼のやり方でド・ポワンシーを排除するかもしれませんし、それは私にとっても全く問題ありません。\nさて、諸君、私の話は聞いたはずです。一ヶ月後、私の邸宅で百万を持ってお待ちしています。 出入りは自由に保証します。";
			link.l1 = "...";
			link.l1.go = "Stivesant_48";
		break;
		
		case "Stivesant_48":
			DialogExit();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			pchar = GetMainCharacter();			
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("Noel");
			sld.dialog.currentnode = "noel_84";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
			sld = CharacterFromID("Stivesant");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Patria_CondotierStivesantInHall", 12.0);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("Stivesant_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			}
		break;
		
		case "Stivesant_49":
			if (sti(pchar.money) >= 1000000)
			{
				dialog.text = "私は一度も疑いませんでしたよ、シャルル・ド・モール副提督殿、あなたがこの金を持ってきてくれることを。 もしかしたら、あなたに要求した額は少なすぎたかもしれませんが、まあいいでしょう……バロンなど、あなたの次の一手の駒に過ぎませんね？地位や金だけでは満足できず、 今度はド・ポワンシーの座まで狙うおつもりでしょう？認めざるを得ませんな、フランス植民地総督の椅子に比べれば、 百万など取るに足らぬ額です！あなたの鉄の支配力があれば、数ヶ月でこの金も取り戻せるでしょう。";
				link.l1 = "百万を受け取れ、マインヘール。約束された帳簿を受け取りたい。";
				link.l1.go = "Stivesant_50";
			}
			else
			{
				dialog.text = "百万集めることに集中したほうがいいですよ、旦那。無駄な訪問で時間を浪費するよりもね。";
				link.l1 = "...";
				link.l1.go = "Stivesant_49_1";
			}
		break;
		
		case "Stivesant_49_1":
			DialogExit();
			npchar.dialog.currentnode = "Stivesant_49";
		break;
		
		case "Stivesant_50":
			pchar.quest.Patria_CondotierStivesantTimeOver.over = "yes"; // снять таймер
			AddMoneyToCharacter(pchar, -1000000);
			GiveItem2Character(pchar, "Reserve_item_01");
			ref itm = ItemsFromID("Reserve_item_01");
			itm.picIndex = 15;
			itm.picTexture = "ITEMS_26";
			itm.price = 0;
			itm.Weight = 2.0;
			itm.name = "itmname_Reserve_item_01_1";
			ChangeItemDescribe("Reserve_item_01", "itmdescr_Reserve_item_01_4");
			dialog.text = "もちろんでございます、副提督。しかめっ面はなさらずに。あなたが総督になれば、 オランダ西インド会社が強欲で好戦的なイギリス人よりも、 はるかに利益をもたらすビジネスパートナーだと分かりますよ。イギリス人に指一本差し出せば、 手ごと持っていかれることをご存じないのですか？もしご存じなければ、痛い目に遭って学ぶことになるでしょう。 ですから、まだお別れは申し上げません。書類はお持ちください。 あなたの男爵がシュヴァリエを打ち負かすだけの有能さを持っていることを願っております。";
			link.l1 = "感謝する。さらばだ、スタイフェサント旦那。";
			link.l1.go = "Stivesant_51";
		break;
		
		case "Stivesant_51":
			DialogExit();
			AddQuestRecord("Patria", "84");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			pchar.quest.Patria_CondotierCabin.win_condition.l1 = "location";
			pchar.quest.Patria_CondotierCabin.win_condition.l1.location = "Curacao";
			pchar.quest.Patria_CondotierCabin.function = "Patria_CondotierCabin";
		break;
		
		case "vanberg_sold":
			dialog.text = "ハハハ！見ろよ！やっぱりジェイコブの言った通りだな――この狐が島に来たのは訳があったんだ。どうやら宝箱にはかなりの金が入ってるらしいぜ。お前、 一人で来るなんてずいぶん無用心じゃねえか、相棒。ま、そのおかげで俺たちの仕事はずっと楽になるけどな！";
			link.l1 = "あのクズどもが俺を見つけやがった！まさかこんなことになるとは……だが、俺は簡単に狩られる獲物じゃねえぞ！";
			link.l1.go = "vanberg_sold_1";			
		break;
		
		case "vanberg_sold_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("vanberg_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "PrepareMassakraInShore");
			AddDialogExitQuest("MainHeroFightModeOn");			
		break;
		
		case "Abihouselady":
			dialog.text = "誰かを探しているのか？";
			link.l1 = "ああ、そうだ。ソロモンとアビゲイル・シュヌールはどこにいる？";
			link.l1.go = "Abihouselady_1";			
		break;
		
		case "Abihouselady_1":
			dialog.text = "もうここには住んでいないんだ。単純に、この場所に住む余裕がなかったのさ。アビゲイルは、かわいそうに、 今は総督の召使いの一人として働いている。自分と父親のために毎日懸命に働いているよ。 ソロモンは毎日酒場で酒を飲んでいる。あの出来事を受け入れられないんだ。今では、 海からそう遠くない小さな小屋で暮らしているよ…";
			link.l1 = "ああ……わかりました、情報ありがとうございます。行かなくては。";
			link.l1.go = "Abihouselady_2";
		break;
		
		case "Abihouselady_2":
			DialogExit();
			NextDiag.CurrentNode = "Abihouselady_3";
		break;
		
		case "Abihouselady_3":
			dialog.text = "他に何か知りたいことはあるかい、旦那？";
			link.l1 = "何でもない、気にするな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abihouselady_3";
		break;
		
		//удаление Мейфенг при провале квеста
		case "TempOffGuard":
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//удаляем атрибут квестового корабля
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)
			{
				pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
				pchar.Ship.name = "A boat";
				SetBaseShipData(pchar);
				SetCrewQuantityOverMax(PChar, 0);//сажаем на тартану
			}
			else
			{
				for(i = 1; i < COMPANION_MAX; i++)
				{
						iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Self.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Self.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			dialog.text = "船長、あなたはオランダ西インド会社所有の船を不正に取得した。私はそれを没収し、 抵抗すれば武力行使も認められている。これはピーテル・スタイフェサントからの命令だ。";
			link.l1 = "ふむ、ピーター・スタイフェサント本人からの命令ならば……船一隻のためにオランダと戦争する気はない。持っていけ。";
			link.l1.go = "TempOffGuard_1";			
		break;
		
		case "TempOffGuard_1":
			dialog.text = "道理をわきまえてくれて助かる。";
			link.l1 = "...";
			link.l1.go = "TempOffGuard_2";
		break;
		
		case "TempOffGuard_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");
		break;
		
		// Jason НСО
		case "arest":
			dialog.text = "もちろん出発の時間だ、しかも護衛付きだぞ。\n衛兵たち！そいつを捕まえろ！";
		    link.l1 = "やれるもんならやってみろ！";
		    link.l1.go = "fight";
		break;
		
		case "fight":
            Pchar.quest.ArestInResidenceEnd.win_condition.l1          = "ExitFromLocation";
		    Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		    Pchar.quest.ArestInResidenceEnd.win_condition             = "ArestInResidenceEnd";
		    Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_LockFightMode(Pchar, true); // ножками путь убегает
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		    LAi_group_Attack(NPChar, Pchar); // не работает на бессмертного мера :(
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"おい、聞いてくれ！この町の住人として、抜き身の剣を持って歩き回らないように頼むぜ。","この町の市民として、お願いだが、抜き身の剣を持って歩き回るのはやめてくれ。");
			link.l1 = LinkRandPhrase("「結構だ。」","「よし。」","おっしゃる通りでございます……");
			link.l1.go = "exit";
		break;
	}
}
