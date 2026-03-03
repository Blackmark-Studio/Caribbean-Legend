// китаец Лонгвэй, подручный Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string 	sAttr, sGun, sBullet, attrL;

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
	if (findsubstr(sAttr, "SetMusketBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetMusketBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
 	    Dialog.CurrentNode = "SetMusketBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "船長。私の名はロンウェイ。ロンウェイはあなたの指揮下に船を置く。ロンウェイ自身もあなたの指揮下だ。 ローデンブルク旦那の命令による。";
			link.l1 = "ごきげんよう、ロンウェイ。シャルル・ド・モール、参上いたしました。 ヤコブ・ファン・ベルクを排除する作戦について、何か手がかりはありますか？";
			link.l1.go = "Longway_friend";
			link.l2 = "会えて嬉しいよ、ロンウェイ。私の名はシャルル・ド・モールだ。無駄にしている暇はない――ローデンブルク旦那は迅速かつ高品質な仕事を評価しているからな。今、ヤーコブ・ファン・ベルグはどこに隠れている？ ";
			link.l2.go = "Longway_neutral";
			link.l3 = "さて、私の名はシャルル・ド・モールですわ！私たちの協力がうまくいくことを願いましょう！\nそれで、ロンウェイ旦那、ヤーコプ・ファン・ベルクを探すにはどこへ行けばよろしいのでしょう？";
			link.l3.go = "Longway_enemy";
			NextDiag.TempNode = "First time";
			pchar.questTemp.HWIC.Holl.JacobCity = SelectJacobCity();
		break;
		
//-----------------------------------------------за Голландию-----------------------------------------------
		case "Longway_neutral":
			dialog.text = "ロンウェイは、俺たちがうまくやれると確信しているぜ、船長。ヤーコプ・ファン・ベルフは現在 "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+"。地元の酒場で彼と会う約束を取り付けた。彼はそこに来るだろう。";
			link.l1 = "出航しようぜ！";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayNeutral = "true";//признак враждебности китайца
		break;
		
		case "Longway_enemy":
			dialog.text = "ローデンブルク旦那の法の命令、ロンウェイのために……ヤーコプ・ファン・ベルフは現在 "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Gen")+"。地元の酒場で彼と会う約束を取り付けた。彼はそこに来るはずだ。";
			link.l1 = "出航しよう！";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayEnemy = "true";//признак враждебности китайца
			Notification_Approve(false, "Longway");
		break;
		
		case "Longway_friend":
			dialog.text = "ロンウェイは全力を尽くすぜ、船長。今ヤコブ・ファン・ベルクは "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"。地元の酒場で彼と会う約束を取り付けた。彼はそこに来るはずだ。";
			link.l1 = "出航しよう！";
			link.l1.go = "Longway_JacobGo";	
			pchar.questTemp.HWIC.Holl.LongwayFriend = "true";//признак враждебности китайца
			Notification_Approve(true, "Longway");
		break;
		
		case "Longway_JacobGo":
			//Лонгвэя - в офицеры
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.HalfImmortal = true;//полубессмертен
			npchar.loyality = 18;
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", -1);
			AddQuestRecord("Holl_Gambit", "1-8");
			ForceHeroAutolevel(npchar);
			SetCharacterPerk(npchar, "Captain");
			AddQuestUserData("Holl_Gambit", "sCity", XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat"));
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Holl.JacobCity, true);
			AddLandQuestMark(characterFromId(""+pchar.questTemp.HWIC.Holl.JacobCity+"_tavernkeeper"), "questmarkmain");
			pchar.questTemp.HWIC.Holl = "JacobOnMain";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 30, false);
			}
			else SetFunctionTimerCondition("JacobOnMainOver", 0, 0, 15, false);
		break;
		
		case "hired":
			dialog.text = "ロンウェイに何ができるんだ、船長？";
			link.l1 = "今のところ何もない。";
			link.l1.go = "exit";
			NextDiag.TempNode = "hired";
		break;
		
		case "MC_GoAway":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			if (pchar.questTemp.HWIC.Holl == "MirageFail")
			{
				dialog.text = "このバカなモンゴル野郎、船長め！俺たちの任務は簡単だった――「ミラージュ」を拿捕して「美鳳」を失わないこと。それなのに、あの船長がいない「ミラージュ」 は楽な獲物だったはずなのに、お前はやり遂げられなかった\nロンウェイはもうお前には仕えないし、顔も見せない。 ロンウェイはローデンブルフ旦那もこの決断を認めてくれると確信している。";
				link.l1 = "てめえもてめえのご主人もくたばっちまえ！";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-10");
			}
			if (pchar.questTemp.HWIC.Holl == "JacobOnMain" || pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "このバカなモンゴル野郎、船長！お前の個人的な問題に時間を食いすぎて、 ヤーコブ・ファン・ベルグに会う暇がなかったじゃねえか。もう奴はここからいなくなっちまった\n "+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Holl.JacobCity+"Dat")+"\n任務を果たせなかったな。ロンウェイはお前に仕えるつもりも、二度と会うつもりもない。 ロンウェイはローデンブルク旦那もこの決断を認めてくれると確信している。";
				link.l1 = "「てめえもてめえの主人もくたばっちまえ！」";
				link.l1.go = "exit";
				AddQuestRecord("Holl_Gambit", "1-9");
			}
			if (pchar.questTemp.HWIC.Holl == "lateVillemstad")
			{
				dialog.text = "船長、あなたは無駄に時間を浪費しただけで何の成果もない。この船はあなたのものじゃないし、 ロンウェイはあんたの下働きでもない。ロンウェイはウィレムスタッドに戻る\nロンウェイはもうあなたに仕えもしないし、会いもしない。ローデンブルク旦那もこの決断を認めてくれるはずだ。";
				link.l1 = "貴様も貴様のご主人もくたばっちまえ！";
				link.l1.go = "exit";
			}
			PChar.quest.Munity = "Deads";
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], false);
			if(sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_MAYFANG)//если сам на Мейфенг
			{
			pchar.Ship.Type = GenerateShipExt(SHIP_TARTANE, true, pchar);
			pchar.Ship.name = "Boat";
			SetBaseShipData(pchar);
			SetCrewQuantityOverMax(PChar, 0);
			}
			else
			{
				for(i=1; i < COMPANION_MAX; i++)
				{
					int iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
						{
							pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
							sld = GetCharacter(sti(pchar.questTemp.HWIC.Holl.CompanionIndex));
							RemoveCharacterCompanion(PChar, sld);
							AddPassenger(PChar, sld, false);
						}
					}
				}
			}
			LAi_CharacterDisableDialog(npchar);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Longway_hire":
			PlaySound("Voice\English\hambit\Longway-03.wav");
			dialog.text = "船長、ロンウェイはローデンブルク旦那のもとを離れた。ロンウェイは二度と彼のもとへは戻らない。 あなたはロンウェイに親切にしてくれたし、勇敢な船長だ。ロンウェイはあなたの召使いとして、 旦那船長の乗組員に加わりたい。\n";
			link.l1 = "召使いとしてじゃなく、士官としてだ！乗船を歓迎するぜ、相棒！";
			link.l1.go = "Longway_hire_1";	
			link.l2 = "いや、いいんだ、ロンウェイ。お前はもう自由の身だ。俺はお前の助けはいらねえよ。";
			link.l2.go = "Longway_exit";	
		break;
		
		case "Longway_exit":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 30.0);
			AddQuestRecord("Holl_Gambit", "1-37");
		break;
		
		case "Longway_hire_1"://нанимаем китайца
			DialogExit();
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "HalfImmortal");
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
		
			npchar.CanTakeMushket = true;
			npchar.Payment = true;
			LAi_SetOfficerType(npchar);
			NextDiag.CurrentNode = "Longway_officer";
			npchar.quest.meeting = true;
			npchar.HoldEquip = true;
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 200, 200);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			AddQuestRecord("Holl_Gambit", "1-38");
			ForceHeroAutolevel(npchar);
			
			//Sinistra - квест Лонгвэя "Путеводная звезда"
			PChar.quest.PZ_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Start.win_condition.l1.location = "Curacao";
			PChar.quest.PZ_Start.win_condition = "PZ_Start";
		break;
		
//---------------------------------------------против всех-------------------------------------------------
		case "Longway_abordage":
			PlaySound("Voice\English\hambit\Longway-02.wav");
			dialog.text = "なぜ止まった？殺せ。ロンウェイは疲れた、ロンウェイは死を望む。シン…許してくれ。";
			link.l1 = "待て、支那野郎。殺そうと思えばすぐにでも殺せるが、まずはお前と話がある。お前の運命はこれからの行動次第だ。 今のところは、俺の貨物室へようこそ！";
			link.l1.go = "Longway_abordage_1";			
		break;
		
		case "Longway_abordage_1":
			AddQuestRecord("Holl_Gambit", "3-45");
		    DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
            DialogExit();
			LAi_SetPlayerType(pchar);
			pchar.questTemp.HWIC.Self = "LongwayPrisoner";
			npchar.lifeday = 0;
			SetFunctionTimerCondition("RemoveLongwayOver", 0, 0, 1, false);//таймер до конца суток, ибо нефиг
		break;
		
		case "Longway_prisoner":
			DelLandQuestMark(npchar);
			dialog.text = "";
			link.l1 = "これで耳元で剣のぶつかる音を聞かずに話せるな。\n聞け、ロンウェイ。俺は情報が必要だ。そしてお前が俺の知りたいことを知ってるのは間違いねえ。\n問題はこうだ――素直に話すか、それとも痛い目を見るか、どっちにする？";
			link.l1.go = "Longway_prisoner_1";			
		break;
		
		case "Longway_prisoner_1":
			dialog.text = "";
			link.l1 = "黙っているのか？まあいい。取引を持ちかけよう。お前の命は助けて、次の陸地で降ろしてやる。その代わり、 ルーカス・ローデンブルクがどこへ、そしてなぜお前を送り込んだのか教えろ。どうだ、取引成立か？";
			link.l1.go = "Longway_prisoner_2";			
		break;
		
		case "Longway_prisoner_2":
			dialog.text = "";
			link.l1 = "お前が英語、オランダ語、フランス語を理解できるのは知っている。それに、耳もいいようだな。だが、 そろそろ口を開いてもらおうか。いずれは知っていることをすべて話してもらうぞ。 中国人は拷問の技術に誇りを持っているのは知っているが、俺たち西洋人もその古い技術を独自に進化させてきたんだ。 ここにいるアロンソは、人の口を割らせる達人だ。彼は俺の船に乗る前、サンティアゴの聖なる異端審問官だった。 聖職者たちから、どんな人間でも自白させるためのあらゆる技を学んだんだ……相手がプロテスタントでなくてもな！\n";
			link.l1.go = "Longway_prisoner_3";			
		break;
		
		case "Longway_prisoner_3":
			dialog.text = "";
			link.l1 = "俺の機知もお前には無駄だったな。だが全部話してもらうぜ、つり目の友よ……全部だ……だがその後、お前は長くは生きられねえ、いや、生かしちゃおかねえ。アロンソと会った後は、 その体がひどく苦しむことになる。だから選べ。真実をすべて話して生きるか、 真実をすべて話して拷問台の上で苦しみながら死ぬかだ。痛みにのたうち回りながらな。わかったか？安心しろ、 ちゃんと神父を呼んでやる。お前の異教徒の魂が地獄の業火から救われるよう、 キリスト教の洗礼を受けさせてやるからな。";
			link.l1.go = "Longway_prisoner_4";
		break;
		
		case "Longway_prisoner_4":
			dialog.text = "";
			link.l1 = "お前の暗い目に疑念が芽生えているのが見えるぜ。なぜ主君の罪のために死ななきゃならねえんだ？ そいつのために命を捨てる価値があるのか？ローデンブルクってやつは、 本当にお前の魂を苦しむ体から引き剥がされるほどの価値があるのか？";
			link.l1.go = "Longway_prisoner_5";			
		break;
		
		case "Longway_prisoner_5":
			dialog.text = "ロンウェイが話す。だがその前に、ロンウェイはお前が約束を守るか確かめたい、船長。";
			link.l1 = "はっ！賢いことを言うじゃねえか！俺が約束するぜ、坊主。";
			link.l1.go = "Longway_prisoner_6";			
		break;
		
		case "Longway_prisoner_6":
			dialog.text = "悪いが、船長、あんたの言葉だけじゃ信用できねえ。情報を手に入れてから俺を殺すつもりだろう！ ロンウェイは保証が欲しいんだ。";
			link.l1 = "手強い交渉だな。どんな保証が欲しいんだ？";
			link.l1.go = "Longway_prisoner_7";			
		break;
		
		case "Longway_prisoner_7":
			dialog.text = "グアドループの南にマリー・ガラントという小さな島がある。ケープ・インアクセスブルだ。 そこにロンウェイを上陸させて、武器を渡せ。\nそうすれば初めてロンウェイがルーカス・ローデンブルクについて知っていることをすべて話してくれるだろう。";
			link.l1 = "お前に俺と交渉する立場なんてねえぞ、中国野郎。";
			link.l1.go = "Longway_prisoner_8";			
		break;
		
		case "Longway_prisoner_8":
			dialog.text = "お前がロンウェイだったとしても同じことをするだろう、船長。拷問されても俺から情報を引き出すのは簡単じゃねえぞ。 ロンウェイは弱っちい白人じゃねえからな。";
			link.l1 = "いいだろう。取引成立だ。ただし警告しておく――俺を騙そうなんて思うなよ。そうしたら、俺が直々にお前をバラバラにしてやる。千通りのやり方で、ゆっくりとな……お前らの皇帝どもがやるみたいにな。\nアロンソ！";
			link.l1.go = "Longway_prisoner_9";
			// belamour legendary edition -->
			link.l2 = "お前の言うことは正しい。だが覚えておけ――ここまで来た俺の邪魔は許さねえ。止めようとするなら、虫けらを踏み潰すようにお前の命を奪うぞ。";
			link.l2.go = "Longway_prisoner_9a";
		break;
		
		case "Longway_prisoner_9a":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_9":
			ChangeCharacterComplexReputation(pchar, "nobility",-5);
			AddCharacterExpToSkill(pchar, "FencingL", 30);
			AddCharacterExpToSkill(pchar, "FencingS", 30);
			AddCharacterExpToSkill(pchar, "FencingH", 30);
			AddCharacterExpToSkill(pchar, "Pistol", 30);
			// <-- legendary edition
			DialogExit();
			NextDiag.Currentnode = "Longway_prisoner_0";
			npchar.greeting = "longway";
			sld = characterFromId("Sailor_3");
			sld.dialog.currentnode = "Sailor_deck_7";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);	
			pchar.quest.RemoveLongwayOver.over = "yes";//снять таймер
			pchar.quest.RemoveLongwayTimer.win_condition.l1 = "Timer";
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 10);
			pchar.quest.RemoveLongwayTimer.function = "RemoveLongwayOver";
			pchar.questTemp.HWIC.Self = "GotoGuadeloupe";
		break;
		
		case "Longway_prisoner_0":
			dialog.text = "マリー・ガラントに到着しましたか、船長？";
			link.l1 = "落ち着け、すぐに着くぜ。";
			link.l1.go = "exit";
			NextDiag.Tempnode = "Longway_prisoner_0";
		break;
		
		case "Longway_prisoner_10":
			dialog.text = "約束を守ったな、船長。ロンウェイも同じだ。ロンウェイの任務について知りたいのか？";
			link.l1 = "はい。しかし、あなた自身の約束を思い出していただきたい。あなたが知っていることを*すべて*私に話してくれると。";
			link.l1.go = "Longway_prisoner_11";			
		break;
		
		case "Longway_prisoner_11":
			dialog.text = "ロンウェイは覚えている。ローデンブルクについて何でも答えるぞ、船長。";
			link.l1 = "話を始めろ。";
			link.l1.go = "Longway_prisoner_12";			
		break;
		
		case "Longway_prisoner_12":
			dialog.text = "「メイフェン」はウィレムスタッド港から北へ、セントクリストファーの岸辺へ向けて航海していた。\n五日後には、ピーター・スタイフェサント指揮下のガレオン船が現れる予定だった。\nロンウェイの命令は、この船を艦長ごと沈めることだった。";
			link.l1 = "天の神よ！ローデンブルクがスタイフェサントを殺せと命じたのか？正気の沙汰じゃないぞ！";
			link.l1.go = "Longway_prisoner_13";			
		break;
		
		case "Longway_prisoner_13":
			dialog.text = "ロンウェイの言うことは本当だぜ、船長。あれはローデンブルク旦那の命令だったんだ。 ロンウェイは気に入らなかったが、命令には逆らわねえんだよ。";
			link.l1 = "いかにも中国人らしいな。お前の主人は一体どんな策を巡らせているんだ？";
			link.l1.go = "Longway_prisoner_14";			
		break;
		
		case "Longway_prisoner_14":
			dialog.text = "もう俺の主人じゃねえよ、船長。ロンウェイはローデンブルク旦那の元には戻らねえ。 ローデンブルクはキュラソーで権力を握ったんだ。マティアス・ベックなんざ簡単な獲物だったし、 ローデンブルクの権威と司令官との繋がりがあれば総督を牢にぶち込むのもたやすいことさ\n残る障害は西インド会社の取締役、スタイフェサント旦那だけだ。スタイフェサントを排除すれば、 ローデンブルクがオランダ領の全ての権力を手中に収めるだろう。";
			link.l1 = "教えてくれ、ロンウェイ。ローデンブルクのような尊敬され、権力もある男が、 なぜあそこまで自分の会社や共和国に逆らうような過激な行動に出たんだ？\nまさか日射病や突然の狂気のせいだなんて言わないでくれよ。";
			link.l1.go = "Longway_prisoner_15";			
		break;
		
		case "Longway_prisoner_15":
			dialog.text = "ロンウェイは自分の耳で聞きたかったんだよ、船長。あんたがカンパニーのパケット船を拿捕して、 ローデンブルクに手紙を届けたんだろ？その理由はその手紙に書いてあったんだ。";
			link.l1 = "なるほどな……ジョン・マードックの記録には、 ローデンブルクが自国に反旗を翻すほど恐れるに足る驚くべきものがたくさんあるようだな。";
			link.l1.go = "Longway_prisoner_16";			
		break;
		
		case "Longway_prisoner_16":
			dialog.text = "他に何か知りたいことはあるか、船長？";
			link.l1 = "はい。他にローデンブルクは何をしたんだ？";
			link.l1.go = "Longway_prisoner_17";			
		break;
		
		case "Longway_prisoner_17":
			dialog.text = "ローデンブルク旦那がお前の死を命じた。ロンウェイはスタイフェサントを追う前にカラカスにいて、 チュアンジャン・ヤコブと会い、指示を与えた。\n";
			link.l1 = "ヤコブ・ファン・ベルク船長？";
			link.l1.go = "Longway_prisoner_18";			
		break;
		
		case "Longway_prisoner_18":
			dialog.text = "よくご存じですね。そうです。チュアンジャン・ヤーコプ・ファン・ベルグがあなたを狙っていますよ、船長。 いずれ見つかるでしょう。ファン・ベルグから長く逃げおおせた者はいません。";
			link.l1 = "奴も血を流すなら、俺が殺せるってことだ。ヴァン・ベルグと自慢の幽霊船は俺が片付けてやる。";
			link.l1.go = "Longway_prisoner_19";			
		break;
		
		case "Longway_prisoner_19":
			dialog.text = "よく知ってるな、船長。ロンウェイからはもう言うことはない。まだ聞きたいことがあれば聞け。";
			link.l1 = "スタイフェサントはセントクリストファーの岸辺の近くにいるのか？";
			link.l1.go = "Longway_prisoner_20";			
		break;
		
		case "Longway_prisoner_20":
			dialog.text = "はい、船長。およそ一週間後にはこの島の岸辺近くで彼のガレオン船を見つけられるでしょう。";
			link.l1 = "いいね！この狐を自分の罠で捕まえてやろう……もう質問はない。知りたかったことはすべて分かった。";
			link.l1.go = "Longway_prisoner_21";			
		break;
		
		case "Longway_prisoner_21":
			dialog.text = "最後にもう一つ忠告だ、船長。ガレオン船に攻撃されずに近づきたいなら、「美鳳（メイフェン）」を連れて行くんだ。";
			link.l1 = "承知しました。情報をありがとうございます。";
			link.l1.go = "Longway_prisoner_22";			
		break;
		
		case "Longway_prisoner_22":
			dialog.text = "ロンウェイは今から出発する。さようなら、船長。";
			link.l1 = "ご武運を、東方の友よ。";
			link.l1.go = "Longway_prisoner_23";			
		break;
		
		case "Longway_prisoner_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "ReturnShoreToNormal", -1);
			npchar.lifeday = 0;
			AddQuestRecord("Holl_Gambit", "3-49");
			pchar.questTemp.HWIC.Self = "MeetingStivesant";
			pchar.quest.Seek_Piter.win_condition.l1 = "location";
			pchar.quest.Seek_Piter.win_condition.l1.location = "Nevis";
			pchar.quest.Seek_Piter.function = "CreatePiterHalleon";
			pchar.quest.RemoveLongwayTimer.over = "yes";//снять прерывание
			SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 8, false); // таймер
			AddMapQuestMarkIsland("Nevis", true);
		break;
		
		//--> ----------------------------------- офицерский блок ------------------------------------------
		case "Longway_officer":
			dialog.text = "「しっかり聞いてるぜ、船長。」";
			// Эпилог
			if (CheckAttribute(pchar, "questTemp.SharlieEpilog_FarewellOfficers") && !CheckAttribute(npchar, "quest.SharlieEpilog_FarewellOfficers"))
			{
				dialog.text = "ご命令は、キャプテン？";
				Link.l1 = ""+npchar.name+"、私はヨーロッパへ向かうことにした — 父のもとへ帰るんだ。道のりは簡単じゃないし、いつ戻れるかも分からない。そろそろ別れの時のようだな。君がここで私を待ち続けるとは思えない — それに安全でもないしな。";
				Link.l1.go = "SharlieEpilog_Longway_1";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				Link.l4 = "ロンウェイ、私はこれから古代インディアンの都市タイアサルへ向かうつもりだ。\nはっきり言っておくが、本当に危険な旅になるし、しかも神秘的なものになる――テレポートの偶像を使ってそこへ行くんだ。\nお前も……一緒に来てくれるか？";
				Link.l4.go = "tieyasal";
			}
			
			////////////////////////казначей///////////////////////////////////////////////////////////
           	// boal отчёт о корабле
			if(CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
			{
			    Link.l11 = "ロンウェイ、船について詳しく報告してくれ。";
			    Link.l11.go = "QMASTER_1";
				
			    // Warship. Автозакупка товара
				Link.l12 = "我々が寄港するたびに、ある品物を必ず仕入れてほしい。";
				Link.l12.go = "QMASTER_2";
			}

			if (CheckAttribute(NPChar, "IsCompanionClone"))//////////////////компаньон//////////////////////////////////////////////
			{
				//dialog.text = "ご命令どおりに参りました、船長。";
				Link.l2 = "あなたにいくつか命令を出さなければならない。";
				Link.l2.go = "Companion_Tasks";
				NextDiag.TempNode = "Longway_officer";// не забыть менять в зависисомости от оффа
				break;
			}
			Link.l1 = "俺の命令を聞け！";
            Link.l1.go = "stay_follow";
			link.l2 = "何もない。下がれ！";
			link.l2.go = "exit";
			NextDiag.TempNode = "Longway_officer";
		break;
		
		/////////////////////////// ответы для казначея ///////////////////////////////////
		case "QMASTER_1":
			dialog.Text = "ロンウェイは今まで一度も会計係になったことはない、船長。ロンウェイはトリニダードからハバナまでどう航海するか、 どれくらい時間がかかるかは教えられる。でもロンウェイは積荷や売上、取引の計算は一切しないんだ。";
			Link.l1 = "おっしゃる通りですね。こんな優秀な航海士を無駄にするのはもったいないですわ。";
			Link.l1.go = "exit";
		break;	

		case "QMASTER_2":
			dialog.text = "ロンウェイは鬼佬とは取引しない、船長。ロンウェイはいつも舵を握ってきたんだ、 古い鷲鼻野郎が最後のエイトピースを値切るような店じゃなくてな。";
			link.l1 = "ふむ、確かにそうだな。お前がいたら商人たちも怯えるだろう。";
			link.l1.go = "exit";
		break;

		//Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
		case "Companion_Tasks":
			dialog.Text = "お聞きします。";
			Link.l1 = "拿捕について話そう。";
			Link.l1.go = "Companion_TaskBoarding";
			Link.l2 = "お前の船について話そう。";
			Link.l2.go = "Companion_TaskChange";
			if (bBettaTestMode) // Только при бета-тесте
			{
				Link.l3 = "しばらく俺の戦隊から離れて、自分の力で運を試してきてほしい。";
				Link.l3.go = "CompanionTravel";
			}
			Link.l8 = "今のところ何もない。";
			Link.l8.go = "exit";
		break;

		case "Companion_TaskBoarding":
			dialog.Text = "ご用件は何でしょうか？";
			Link.l1 = "敵船には乗り込むな。自分と乗組員の身を守れ。";
			Link.l1.go = "Companion_TaskBoardingNo";
			Link.l2 = "敵船に積極的に乗り込んでほしい。";
			Link.l2.go = "Companion_TaskBoardingYes";
		break;

		case "Companion_TaskChange":
			dialog.Text = "ご希望は何でしょうか？";
			Link.l1 = "乗り込んだ後で他の船と交換するな。あの船は貴重すぎるんだ。";
			Link.l1.go = "Companion_TaskChangeNo";
			Link.l2 = "敵船に乗り込んだとき、もしまともな船なら自分のものにできるぜ。";
			Link.l2.go = "Companion_TaskChangeYes";
		break;

		case "Companion_TaskBoardingNo":
			dialog.Text = "了解だ。";
			Link.l1 = "楽にしてくれ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = false;
		break;

		case "Companion_TaskBoardingYes":
			dialog.Text = "承知いたしました。";
			Link.l1 = "楽にしてくれ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanBoarding = true;
		break;

		case "Companion_TaskChangeNo":
			dialog.Text = "あいよ。";
			Link.l1 = "承知しました。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

		case "Companion_TaskChangeYes":
			dialog.Text = "承知いたしました。";
			Link.l1 = "楽にしてくれ。";
			Link.l1.go = "exit";
			NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
	//	<========////////////////////////////////////////
		case "stay_follow":
            dialog.Text = "ご命令は、船長？";
            Link.l1 = "「踏みとどまれ！」";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "俺について来い、遅れるなよ！";
            Link.l2.go = "Boal_Follow";
			if(CheckAttribute(NPChar, "equip.gun"))
			{
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "火器の弾薬の種類を変更する。";
					Link.l3.go = "SetGunBullets";
				}	
			}
			if(CheckAttribute(NPChar, "equip.musket"))
			{
				if(CheckAttribute(NPChar, "chr_ai.musket.bulletNum") && sti(NPChar.chr_ai.musket.bulletNum) > 1)
				{
					Link.l4 = "マスケット銃の弾薬の種類を変更する。";
					Link.l4.go = "SetMusketBullets";
				}
					Link.l5 = "戦闘用の主武器を変更しろ。";
					Link.l5.go = "SetPriorityMode";
					Link.l6 = "ロンウェイ、特定の距離から敵に砲撃してほしい。";
					Link.l6.go = "TargetDistance";
			}	
		break;
		
		case "SetGunBullets":
			Dialog.Text = "弾薬の種類を選択：";
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

		case "SetMusketBullets":
			Dialog.Text = "弾薬の種類を選択してください：";
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.musket.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetMusketBullets2":
			i = sti(NPChar.SetMusketBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, MUSKET_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, MUSKET_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, MUSKET_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetMusketBullets");
			DialogExit();
		break;
		
		case "SetPriorityMode":
			Dialog.Text = "戦闘開始時、あなたが使うのは：";
			Link.l1 = "Blade";
			Link.l1.go = "BladePriorityMode";
			Link.l2 = "Musket";
			Link.l2.go = "MusketPriorityMode";
		break;
		
		case "BladePriorityMode":
			SetPriorityMode(NPChar, 1);
			DialogExit();
		break;
		
		case "MusketPriorityMode":
			SetPriorityMode(NPChar, 2);
			DialogExit();
		break;
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "態度が変わったぞ！";
            Link.l1 = "下がってよい。";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "態度が変わったぞ！";
            Link.l1 = "下がってよい。";
            Link.l1.go = "Exit";
        break;
		
		//--> задать дистанцию стрельбы
		case "TargetDistance":
			dialog.text = "「それで、その距離とはどれくらいだ？お忘れなく、旦那船長、 マスケット銃じゃ二十メートル以上先の的には当たらねえぞ。」";
			link.l1 = "";
			Link.l1.edit = 3;
			link.l1.go = "TargetDistance_1";			
		break;
		
		case "TargetDistance_1":
			iTemp = sti(dialogEditStrings[3]);
			if (iTemp < 0)
			{
				dialog.text = "「どういう意味ですか、船長閣下？」";
				link.l1 = "すまない、時々君が冗談に弱いことを忘れてしまうんだ。";
				link.l1.go = "exit";
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "俺はここで踏ん張って、近づいてくる敵には容赦なく撃つぜ。そうしてほしいのか？";
				link.l1 = "ああ、その通りだ、ロンウェイ。";
				link.l1.go = "exit";
				npchar.MusketerDistance = 0;
				break;
			}
			if (iTemp > 20)
			{
				dialog.text = "それは遠すぎますぞ、船長閣下。群衆なら当たるかもしれませんが、単独の標的を狙うのは無理です。";
				link.l1 = "試してみる価値はあるかもしれないが、まあいいだろう。";
				link.l1.go = "exit";
				npchar.MusketerDistance = 20.0;
				break;
			}
			dialog.text = "「承知いたしました、船長閣下。」";
			link.l1 = "素晴らしい。";
			link.l1.go = "exit";
			npchar.MusketerDistance = iTemp;
		break;
		//<-- задать дистанцию стрельбы
	//<-- ----------------------------------- офицерский блок ----------------------------------------
	
	// на Тайясаль
		case "tieyasal":
			dialog.text = "ロンウェイはずっとあなたを追い続けてきた。\nロンウェイはこれからも変わらずあなたについていく。\nロンウェイは自分の船長を決して見捨てない。";
			link.l1 = "ありがとう、ロンウェイ！君のことを信じて正解だったよ。";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "いつ始めるんだ？";
			link.l1 = "少し後だ。俺たちはそのために準備しないとな。";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			DialogExit();
			AddQuestRecord("Tieyasal", "24");
			npchar.quest.Tieyasal = "teleport";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// Эпилог
		case "SharlieEpilog_Longway_1":
			dialog.text = ""+npchar.name+"、自分は尊敬するキャプテンの友だと思ってる。どこへでもついて行く覚悟ある — ヨーロッパであっても。";
			link.l1 = "でも覚えてるだろう？ここで異国の者がどう扱われるか。ヨーロッパじゃ、それがもっと酷いんだ。もちろん、君を守りたいけど — 視線や嘲笑までは守れない。だから命令なんてできない。君自身が決めてくれ：一緒に来るか、それとも…";
			link.l1.go = "SharlieEpilog_Longway_2";
		break;

		case "SharlieEpilog_Longway_2":
			dialog.text = ""+npchar.name+" そんな扱いにはもう慣れてる。チャン・シンが死んだ後、キャプテンだけがロングウェイの心に残った。俺はあなたの背中を守るためについて行く。";
			link.l1 = "そうか… 君の忠誠心には感謝している、そして一緒にいてくれることを心から嬉しく思う。実のところ、少し君が羨ましいよ。中国も見た、カリブも見た — 今度はヨーロッパだ。そんな長い旅を経験できる者はそういない… ヴァン・マーデンが君に与えた名前は、まるで預言だったな。";
			link.l1.go = "SharlieEpilog_Longway_3";
		break;

		case "SharlieEpilog_Longway_3":
			dialog.text = "...";
			link.l1 = "出航は2週間後だ。その前に、酒場で盛大に出発を祝おうと思ってる。もちろん君も招待してる。断るのはナシだぞ。";
			link.l1.go = "SharlieEpilog_Longway_4";
		break;

		case "SharlieEpilog_Longway_4":
			dialog.text = ""+npchar.name+" 断るつもりなんてない。俺、行く、キャプテン。";
			link.l1 = "その返事を期待していたよ。飲み会が始まる時には知らせる。それまでは他のことを片付けておく。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Longway_officer";
			npchar.quest.SharlieEpilog_FarewellOfficers = true;
			pchar.questTemp.SharlieEpilog_Longway = true;
			pchar.questTemp.SharlieEpilog_Friends = sti(pchar.questTemp.SharlieEpilog_Friends) + 1;
		break;
	}
}

string SelectJacobCity()
{
	string sTemp;
	switch (hrand(4))
	{
		case 0: sTemp = "Cumana" break;
		case 1: sTemp = "Caracas" break;
		case 2: sTemp = "Maracaibo" break;
		case 3: sTemp = "Cartahena" break;
		case 4: sTemp = "Portobello" break;
	}
	return sTemp;
}
