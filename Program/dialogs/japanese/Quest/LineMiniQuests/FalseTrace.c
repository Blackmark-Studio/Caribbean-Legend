void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "バグです。ご連絡ください。";
			link.l1 = "ああ、いいぜ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "FalseTrace":
			DelMapQuestMarkCity(pchar.questTemp.FalseTrace.StartCity);
			dialog.text = "こんにちは、船長……ええと……ゴホン！くそったれな鉱山め……自己紹介させてもらうぜ。アダム・レイナーだ。俺は単純な男で、前置きは好きじゃねえから、さっさと言うぜ。 いい稼ぎをしたくねえか？お互い一人じゃ無理な、小さな商売を持ちかけたいんだ。";
			link.l1 = "へっ！いい金になるって？面白いじゃねえか。話を聞こう、アダム。";
			link.l1.go = "FalseTrace_1";
			link.l2 = "悪いが、あんたはどうも信用できねえんだ。だから取引はしねえよ。";
			link.l2.go = "FalseTrace_exit";
		break;
		
		case "FalseTrace_exit":
			dialog.text = "信用できるって？ははっ！人は見た目で判断しちゃいけねえぜ。まあ、いいさ。せっかく楽に稼げるチャンスを逃したな。 もっと話の分かる奴を探すとするか……";
			link.l1 = "話はこれで終わりだ、旦那。じゃあな！";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_exit_1":
			DialogExit();
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "questTemp.FalseTrace");
		break;
		
		case "FalseTrace_1":
			//выбираем целевой пункт
			switch (hrand(2))
			{
				case 0: 
					pchar.questTemp.FalseTrace.DayQty = 18;
					pchar.questTemp.FalseTrace.TargetCity = "Beliz";
					pchar.questTemp.FalseTrace.TargetShore = "Shore8";
				break;
				case 1: 
					pchar.questTemp.FalseTrace.DayQty = 22;
					pchar.questTemp.FalseTrace.TargetCity = "Marigo";
					pchar.questTemp.FalseTrace.TargetShore = "Shore41";
				break;
				case 2: 
					pchar.questTemp.FalseTrace.DayQty = 20;
					pchar.questTemp.FalseTrace.TargetCity = "Santodomingo";
					pchar.questTemp.FalseTrace.TargetShore = "Mayak8";
				break;
			}
			pchar.questTemp.FalseTrace.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.questTemp.FalseTrace.Mation = sti(npchar.nation);
			dialog.text = "カッハ！あんたみたいな頭の回転が速い船長と取引できて嬉しいぜ。さて、仕事は簡単だ： そこそこの銀を積んだフリュート船が、まもなくこの辺りの港の一つから出航する。たった一隻、護衛なしだ。 バカみてえだろ？カ、カッハ\n 楽勝だぜ。俺が場所と時間を教える、あんたが獲物を取る、そして俺が取り分をもらうってわけだ。";
			link.l1 = "「もちろん、今すぐ現金で受け取りたいんだろう？」";
			link.l1.go = "FalseTrace_2";
		break;
		
		case "FalseTrace_2":
			dialog.text = "俺がみすぼらしいチンピラに見えるか、船長？冗談じゃねえ。俺もこの襲撃に加わるぜ、一緒にやろうじゃねえか。 戦いの最中に船倉でじっとしてるつもりはねえ、むしろ逆だ――一時的でいいから、お前の士官として斬り込み隊に加えてくれ\n俺は自分の仕事を知ってるし、刺すのも撃つのも心得てる。だからお前と同じように命を張る……けほっ、けほっ！フリュート船を奪ったら、取り分はきっちり払ってもらうぜ。";
			link.l1 = "「お前は自分の取り分をどれだけ主張するつもりだ？」";
			link.l1.go = "FalseTrace_3";
		break;
		
		case "FalseTrace_3":
			dialog.text = "俺は欲張りな男じゃねえよ、船長。俺の取り分は、俺の古いロングボートの船倉に積める分だけだ――せいぜい銀200箱ってとこさ。俺の情報によれば、フリュート船には銀が2,000箱は積まれてるらしい。だから、俺はその十分の一をもらうぜ。公平だろ、そう思わねえか？";
			link.l1 = "情報だけで分け前の一割だと？そんな情報、地元の酒場で酔っ払いからラム一杯で買えるぜ。いや、 俺たちは同じ道を行くわけじゃねえ、相棒！";
			link.l1.go = "FalseTrace_4";
			link.l2 = "ふむ。まあ、同意してやるよ。申し出を受けるぜ、アダム。乗船を歓迎する。さて、お前の情報についてだが――どこから来て、どこへ向かう、いつの話で、船の名前は何だ？";
			link.l2.go = "FalseTrace_5";
		break;
		
		case "FalseTrace_4":
			dialog.text = "なんてケチな奴だな、船長！そういうことなら、お前には何もやらねえぜ！じゃあな！";
			link.l1 = "幸運を祈るぜ！お前の怪しい企みには、他の間抜けを探しな！";
			link.l1.go = "FalseTrace_exit_1";
		break;
		
		case "FalseTrace_5":
			dialog.text = "フリュートの名前は "+pchar.questTemp.FalseTrace.ShipName+"、彼女はカルタヘナを出港して航海に出る "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"……だが、あまり時間がないんだ。せいぜい二週間、長くて三週間ってところだ。三週間以内に彼女を見つけられなければ、 すべて終わりだ。";
			link.l1 = "じゃあ、時間を無駄にするな！冒険が俺たちを呼んでるぜ！";
			link.l1.go = "FalseTrace_6";
		break;
		
		case "FalseTrace_6":
			DialogExit();
			NextDiag.CurrentNode = "FalseTrace_officer";
			DelLandQuestMark(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			AddPassenger(pchar, npchar, false);
			AddQuestRecord("FalseTrace", "1");
			AddQuestUserData("FalseTrace", "sCity1", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen"));
			AddQuestUserData("FalseTrace", "sCity2", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity));
			AddQuestUserData("FalseTrace", "sShip", pchar.questTemp.FalseTrace.ShipName);
			//установим таймер на генерацию энкаунтера
			pchar.quest.False_Trace_2.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_2.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.False_Trace_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2);
			pchar.quest.False_Trace_2.function = "CreateFalseTraceGaleonOnMap";
			SetFunctionTimerCondition("FalseTraceGaleonOver", 0, 0, sti(pchar.questTemp.FalseTrace.DayQty)+2, false);//таймер
		break;
		
		case "FalseTrace_officer":
			dialog.text = "何かご用ですか、船長？";
			link.l1 = "何でもない、気にするな。";
			link.l1.go = "exit";
			NextDiag.TempNode = "FalseTrace_officer";
		break;
		
		case "FalseTrace_7":
			chrDisableReloadToLocation = true;
			dialog.text = "俺に会いたかったのかい、船長？";
			link.l1 = "こうなることは分かってたんじゃねえか…銀はどこだ、くそっ！？どこにある！？お前に言ってるんだぞ！フリュート船の船長が、あれは補給船だって言ってたぜ！ お前、俺に嘘つきやがったな！";
			link.l1.go = "FalseTrace_8";
		break;
		
		case "FalseTrace_8":
			dialog.text = "落ち着いてください、船長。全部説明してみます。";
			link.l1 = "もちろんだ！もう落ち着いたぜ！今お前がヤードアームに吊るされていないのは、 俺がまだお前の動機を理解できていないからだけだ。俺と一緒にこのフリュート船を追いかけてきたくせに、 銀がないことは最初から知っていたんだろう。だから、ちゃんと説明してくれよ。";
			link.l1.go = "FalseTrace_9";
		break;
		
		case "FalseTrace_9":
			dialog.text = "ああ、本当に騙したぜ、船長。でもな、俺が欲しかったことをやらせるには、それしか方法がなかったんだ……捕まえるために……けほっ、けほっ！この忌々しいフリュート船をな。\nでも、必ず借りは返すと約束するぜ。さて、なぜこんなことをしたのか話させてくれ。 あのフリュート船で女を見つけたか？船員たちがその女をお前の船に連れて行くのを見たんだ……";
			link.l1 = "ふん……つまり、お前はあの娘が欲しかったのか？だから俺に海戦を仕掛けさせて、あんなに多くの人間を殺させたってわけか！？ ";
			link.l1.go = "FalseTrace_10";
		break;
		
		case "FalseTrace_10":
			dialog.text = "俺の女房だ。カトリーヌ・レイナー。三か月前にこの情けない船長と一緒に俺の元から逃げやがった。 あいつらを探すために手を尽くしたが、ついに見つけたんだ。二人ともこれから\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+"。カテリーヌを連れ戻してあの女たらしにケリをつけるには、これ以上の方法は思いつかなかったぜ\n本当のことを言ったら、お前は逃げ出してただろう。だから、 銀でいっぱいのフリュート船の旨い話をでっちあげるしかなかったんだ。";
			link.l1 = "ふん…お前の女房に逃げられたんだろ？面白いじゃねえか！";
			link.l1.go = "FalseTrace_11";
		break;
		
		case "FalseTrace_11":
			dialog.text = "これは俺の正妻だ。俺は彼女を愛してるし、他の誰にも彼女と一緒になる権利なんてねえ！あのろくでなしが、俺が……留守の間にロマンスだの何だのと甘い嘘を吹き込んだんだ。女ってもんを知らねえのか？ 彼女はそんな戯言を信じちまって、馬鹿な娘だが、あいつと駆け落ちしやがったんだ。";
			link.l1 = "よし、聞けよ、俺はお前の家庭の事情なんざ興味ねえから、女房とは自分で片付けろ。だが、 俺の損失を補償するって言ったよな？聞き間違いじゃねえよな？";
			link.l1.go = "FalseTrace_12";
		break;
		
		case "FalseTrace_12":
			if (pchar.basenation == SPAIN || pchar.basenation == HOLLAND)
			{
				pchar.questTemp.FalseTrace.QuestCity = "Portobello";
				pchar.questTemp.FalseTrace.QuestShore = "Shore48";
			}
			else
			{
				pchar.questTemp.FalseTrace.QuestCity = "SantaCatalina";
				pchar.questTemp.FalseTrace.QuestShore = "Shore54";
			}
			dialog.text = "ああ、そうだ、船長。俺の言った通りだぜ。貸し借りってやつさ。今は金がねえが、 カテリーヌと俺を連れて行ってくれれば "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+"、まったく手間をかけずに金を手に入れられる場所について、確実な情報を教えてやるぜ。";
			link.l1 = "それは面白いな。で、なぜ今すぐにその絶対に信頼できる情報を教えてくれねえんだ？";
			link.l1.go = "FalseTrace_13";
		break;
		
		case "FalseTrace_13":
			dialog.text = "なぜなら、俺はまだその情報を持っていないんだ。詳しく説明しよう。 スクイントアイド・ソリーって名の運のいい旦那がいてな――聞いたことあるか？――そいつがブルーウェルドの近くにある金鉱を襲うつもりなんだ\nある出来事のせいで、ソリーは金を全部隠し場所に置いて、何人か見張りをつけて守らせることになる。 本人は徒歩でベリーズかブルーウェルドまで行って船を手に入れるつもりだ\n俺はソリーの手下の中に密偵を潜り込ませてある。そいつが俺をそこで待っているんだ "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+"。そこに錨を下ろしたら、あいつがソリーの隠し財宝の場所を教えてくれるだろう\nお前はそこへ行って、見張りを片付けて金貨を全部自分のものにしろ。俺がやるつもりだったが、 今の状況を考えると全部お前に任せるぜ。報酬はいらねえ。";
			link.l1 = "お前の話は、前に銀を積んだフリュート船の作り話とよく似てるじゃねえか。俺はすでに一度騙されたんだぜ。 今回は嘘じゃないって、どうやって保証できるんだ？";
			link.l1.go = "FalseTrace_14";
		break;
		
		case "FalseTrace_14":
			dialog.text = "俺の言葉を信じてくれ。他に保証なんてねえ。でも本当だ、誓うぜ、けっ…かっ…くそっ、鉱山め！";
			link.l1 = "よし。もう行け、言ったことについて考えてみる。";
			link.l1.go = "FalseTrace_15";
		break;
		
		case "FalseTrace_15":
			dialog.text = "あまり考え込むなよ。お前も分かってるだろうが、細目のソリーが自分の宝を取り戻しに戻ってくるぜ。俺の計算だと、 お前がそこにたどり着くまであと二週間しかねえ\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+".";
			link.l1 = "心得ておくよ。さて、今すぐ船員部屋に行って水夫たちと合流しなさい。 到着するまでは奥さんと離れていたほうがいいだろう。もう行っていいぞ。";
			link.l1.go = "FalseTrace_16";
		break;
		
		case "FalseTrace_16":
			DialogExit();
			LAi_SetActorType(npchar);
			pchar.questTemp.FalseTrace = "TalkCabinWoman";
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "TalkSelf_Quest", 3.0);
			SetFunctionTimerCondition("FalseTraceSollyOver", 0, 0, 15, false);//таймер
			AddQuestRecord("FalseTrace", "5");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_17":
			dialog.text = "俺を呼んだか、船長？";
			link.l1 = "ああ。アダム・レイナー、俺はお前を逮捕して閉じ込める。お前は俺を騙したんだ、他に手はねえから、 お前を隔離して当局に引き渡すしかねえんだ。";
			link.l1.go = "FalseTrace_18";
		break;
		
		case "FalseTrace_18":
			dialog.text = "本当か？そうすると思ってたぜ、船長。特にあんたが船倉に来て、あの他人の女房を盗む汚ねえ野郎と話し込んだ後はな。 あんたはあいつの味方につくと決めたんだろ、船長？";
			link.l1 = "お前には関係ねえ。俺を利用しやがって、裏切りまでして、今度はまたくだらねえ宝の話で俺を騙そうってのか！ ボースン、こいつを連れて行け！";
			link.l1.go = "FalseTrace_19";
		break;
		
		case "FalseTrace_19":
			dialog.text = "クハッ、そんなに急ぐなよ、船長……お前の水夫長と他の船員たちは、しばらくここに入ってこれねえぜ。ドアに鍵をかけたのに気づかなかったか？ 今ここには俺たち二人きりだ――お前と俺だけだ。\nさあ見せてみろよ、船長、お前の本性を！";
			link.l1 = "本気か？自分に勝ち目があるとでも思ってるのか！？後悔するぜ、この野郎！";
			link.l1.go = "FalseTrace_20";
		break;
		
		case "FalseTrace_20":
			DialogExit();
			NextDiag.currentnode = "FalseTrace_21";
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetHP(npchar, 100+MOD_SKILL_ENEMY_RATE*35, 100+MOD_SKILL_ENEMY_RATE*35); // belamour с 40 хп боец из него никудышный
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10.0, true, "FalseTrace_capture");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_21":
			dialog.text = "";
			link.l1 = "それでいい……武器を捨てろ、このろくでなしめ！甲板長！こいつを手錠につないで船倉にぶち込め！";
			link.l1.go = "FalseTrace_22";
		break;
		
		case "FalseTrace_22":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			bQuestDisableMapEnter = false;
			RemovePassenger(Pchar, npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			Pchar.questTemp.FalseTrace.PrisonerAdamIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			LAi_SetPlayerType(pchar);
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(npchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(npchar, CIRASS_ITEM_TYPE);
			sld = &Characters[sti(Pchar.questTemp.FalseTrace.PrisonerIDX)];
			ReleasePrisoner(sld); //освободили пленника
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "LifeDay") //постоянный персонаж
			GiveItem2Character(sld, "blade_10");
			EquipCharacterbyItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterbyItem(sld, "pistol1");//патроны не даю - все одно для антуражу
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
			AddComplexSelfExpToScill(40, 40, 40, 40);
			AddQuestRecord("FalseTrace", "11");
			AddQuestUserData("FalseTrace", "sShore", XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore+"Gen"));
			pchar.questTemp.FalseTrace = "AdamPrisoner";
		break;
		
		case "FalseTrace_23":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "妻を連れ戻してくれてありがとう、船長！アダム・レイナーはあんたに借りができたぜ、絶対に忘れねえ、はは、誓って……ゴホッ！くそっ、地雷め！さて、片目のソリーのことだが、俺の部下がもう全部詳しく教えてくれた。 ソリーはサンファン・デル・ノルテ湾の洞窟に戦利品を全部隠したらしい。本人は今ブルーウェルドにいる\n急いだほうがいい、俺の仲間によれば、あんたには五日しかない。仲間を連れて行けよ、ソリーの野郎どもは手強いから、 きっと手こずるぜ\nそろそろお別れの時間だな。改めてありがとう、船長、幸運を祈るぜ！";
			link.l1 = "幸運を祈るぜ、アダム。奥さんを怒らせるんじゃねえぞ！";
			link.l1.go = "FalseTrace_Remove_exit";
			SetFunctionTimerCondition("FalseTraceBonanzaOver", 0, 0, 5, false);//таймер
			pchar.quest.False_Trace_4.win_condition.l1 = "location";
			pchar.quest.False_Trace_4.win_condition.l1.location = "Shore55";
			pchar.quest.False_Trace_4.function = "FalseTrace_SollyBonanza";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddQuestRecord("FalseTrace", "14");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
		break;
		
		case "FalseTrace_24":
			pchar.quest.FalseTraceSollyOver.over = "yes"; //снять таймер
			dialog.text = "はっ！なんで俺たちがこの湾に上陸したんだ、船長？俺の部下は港で待ってるって言っただろうが "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"！ジャングルを徒歩で行くつもりか？";
			link.l1 = "見当違いだぜ、アダム。お前のくだらねえ話をまた信じると思ったのか？俺を完全な馬鹿だと思ってるのか？ 今回はお前の女房と取引したんだ。";
			link.l1.go = "FalseTrace_25";
		break;
		
		case "FalseTrace_25":
			dialog.text = "「なんだと！？はっ！俺の女房とどんな取引だって？何を言ってやがる、この腐れ魚め！？」";
			link.l1 = "お前の嘘の情報のせいで、俺は空っぽのフリュート船を拿捕して、その船長を殺しちまった。今さら後悔しても遅いが、 やったことを悔やんでいるぜ。お前の女房はその水夫に惚れてたらしいな。だからこそ、俺にお前を殺せと頼んだんだ。 だから今、俺たちはこの入り江にいるってわけさ。";
			link.l1.go = "FalseTrace_26";
		break;
		
		case "FalseTrace_26":
			dialog.text = "信じられねえ！カトリーヌ……なんて女だ！まあ、お前もそのうち報いを受けるだろうよ……で、あの女はどうやってお前に報酬を払うって言ったんだ、間抜けめ？あいつは一文無しだぜ、 あの船長と逃げるために宝石まで全部売っちまったんだからな！";
			link.l1 = "それはお前の知ったことじゃねえ、ろくでなし。だが、そろそろ話は終わりだ。地獄に送ってやるぜ――とっくにそこにいるべきだったんだからな！";
			link.l1.go = "FalseTrace_27";
		break;
		
		case "FalseTrace_27":
			dialog.text = "やってみろよ、腐ったニシン野郎！";
			link.l1 = "...";
			link.l1.go = "FalseTrace_28";
		break;
		
		case "FalseTrace_28":
			DialogExit();
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_AdamDead");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_abordage":
			dialog.text = "ああ！なんで俺の船を襲いやがったんだ、このクズ野郎！全く理解できねえ……";
			link.l1 = "子羊のふりなんかするなよ、船長。お前がどんな積み荷を運んでるか知ってるんだ。それが俺には必要なんだよ。";
			link.l1.go = "FalseTrace_abordage_1";
		break;
		
		case "FalseTrace_abordage_1":
			dialog.text = "「積み荷だと？ははっ！ここでどんな積み荷を期待してたんだ？俺の船倉は空っぽだぜ！」";
			link.l1 = "何だと、この野郎！もう一度言ってみろ！";
			link.l1.go = "FalseTrace_abordage_2";
		break;
		
		case "FalseTrace_abordage_2":
			dialog.text = "もう一度言うが、俺の船には積み荷なんてねえ。このフリュート船は補給船で、向かっているのは "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.TargetCity)+" 兵士たちのために砲弾と食糧の積荷を運ぶためだ。";
			link.l1 = "俺を騙そうってのか。お前の船倉には銀がぎっしり詰まってるはずだ。話が終わったら、しっかり調べさせてもらうぜ……";
			link.l1.go = "FalseTrace_abordage_3";
		break;
		
		case "FalseTrace_abordage_3":
			dialog.text = "銀のことを誰に聞いたのか知らねえが、そんなのはまったくのデタラメだ……俺はお前に負けたから、もう諦めるぜ。ほら、俺の剣だ。さあ、船倉を調べに行けよ。中は空っぽだ。";
			link.l1 = "諦めるのか？いや、俺には証人なんていらねえ。剣を取って戦え、さもねえと羊みてえに腹を裂いてやるぞ。";
			link.l1.go = "FalseTrace_abordage_4";
			link.l2 = "理性を見せてくれてよかったな。身代金を取れそうだぜ……おい、野郎ども、船長を船倉にぶち込め！";
			link.l2.go = "FalseTrace_abordage_5";
		break;
		
		case "FalseTrace_abordage_4":
			DialogExit();
			pchar.questTemp.FalseTrace.KillCaptain = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "FalseTrace_AfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
		break;
		
		case "FalseTrace_abordage_5":
			DialogExit();
			pchar.questTemp.FalseTrace.CapPrisoner = "true";//атрибут квеста
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "FalseTrace_AfterFight", 3.0);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
			pchar.questTemp.FalseTrace.CapName = GetFullName(npchar);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "FalseTrace_wife":
			dialog.text = "「お前があいつを殺したんだな、この野郎！悪党め！かわいそうな」 "+pchar.questTemp.FalseTrace.CapName+"!";
			link.l1 = "「何だい？どこから来たんだい、お前さん？」";
			link.l1.go = "FalseTrace_wife_1";
		break;
		
		case "FalseTrace_wife_1":
			dialog.text = "お前がやったことのすべてのせいで地獄で焼かれるぞ。くたばれ！";
			link.l1 = "落ち着け、お嬢ちゃん！俺を呪って運を試すんじゃねえぞ――さもないとお前も船長の後を追わせることになるからな！";
			link.l1.go = "FalseTrace_wife_2";
		break;
		
		case "FalseTrace_wife_2":
			dialog.text = "お前……お前は女に手を上げるなんて、できやしないだろう！";
			link.l1 = "そんなことするまでもねえさ。撃ち殺してやることもできるし、船から放り投げてサメに任せるって手もある……さあ、何をぐずぐずしてやがる？俺の船へ行け。怖がることはねえ――おとなしくしてりゃ、誰にも手出しさせねえし、俺もお前には指一本触れねえよ……";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_3":
			DialogExit();
			pchar.quest.False_Trace_AfterBattle.over = "yes";
			pchar.quest.FalseTraceGaleonOver.over = "yes";
			if (CheckAttribute(pchar, "questTemp.FalseTrace.CapPrisoner")) AddQuestRecord("FalseTrace", "");
			else AddQuestRecord("FalseTrace", "");
			sld = characterFromId("Mugger");
			DeleteAttribute(sld, "HalfImmortal");
			RemovePassenger(Pchar, sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DoQuestCheckDelay("LAi_EnableReload", 4.0);
			bQuestDisableMapEnter = true;
			pchar.questTemp.FalseTrace = "TalkCabin";
			AddQuestRecord("FalseTrace", "4");
		break;
		
		case "FalseTrace_wife_4":
			dialog.text = "「な…何をあいつにするつもりだ？」";
			link.l1 = "「なんだい？どこから来たんだい、おチビちゃん？」";
			link.l1.go = "FalseTrace_wife_5";
		break;
		
		case "FalseTrace_wife_5":
			dialog.text = "Poor "+pchar.questTemp.FalseTrace.CapName+"！教えてくれ――あいつを殺すつもりなのか？やめてくれ……";
			link.l1 = "いいか、嬢ちゃん――もし俺があいつを殺したかったら、とっくにやってるさ。あいつは船倉に閉じ込めておく。あとは解放するか、 身代金を取るか……まあ、後者の方がありそうだな。さあ、いい子だから俺の船に乗ってくれ。怖がるなよ――おとなしくしていれば、誰にも手出しはさせねえし、俺自身もお前には指一本触れねえよ……";
			link.l1.go = "FalseTrace_wife_3";
		break;
		
		case "FalseTrace_wife_6":
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "俺に何の用だ？言った通りサメの餌にでもするつもりか？お前は俺の人生を滅茶苦茶にして……";
				link.l1 = "さあ、お嬢さん。誰もあんたをどこかに放り投げたりしないよ。俺はただ状況をはっきりさせたいだけさ、 俺がこのフリュート船を襲ったのはあんたのせいであって、他に理由はないんだからな。";
				link.l1.go = "FalseTrace_wife_7";
			}
			else
			{
				dialog.text = "俺に何の用だ？どこにいるんだ "+pchar.questTemp.FalseTrace.CapName+"「身代金か？身代金が必要なのか？」";
				link.l1 = "よし、お嬢さん、くだらねえ質問攻めはもう終わりにしようぜ。あんたをここに呼んだのはそんな理由じゃねえんだ。 ひとつだけはっきりした事実があるんだが、それはあんたにも興味深いはずだぜ。";
				link.l1.go = "FalseTrace_wife_20";
			}
		break;
		
		case "FalseTrace_wife_7":
			dialog.text = "俺のせいだって？お前が俺たちの船を襲って、俺の愛しい人を殺したのが俺のせいだって言うのか？かわいそうな "+pchar.questTemp.FalseTrace.CapName+"「…お前に何をしたんだ？自分のやったことはすべて、主に裁かれるぞ…」";
			link.l1 = "いつものシチューだな！サメの話に戻るか？";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_8"://ноды пересечения - старт
			dialog.text = "";
			link.l1 = "今は静かか？よし。じゃあ、俺の話を聞け！俺があの船を襲ったのは、 そこにかなりの銀貨が積まれてるって情報を掴んだからだ。その情報はアダム・レイナーから手に入れたんだ。";
			link.l1.go = "FalseTrace_wife_9";
		break;
		
		case "FalseTrace_wife_9":
			dialog.text = "あっ！なんだって！？アダム？どこだ？ここにいるのか？";
			link.l1 = "ほう、その名前……カトリーヌを知っているんだな。\nそして見ての通り、俺はすでにお前のことを全部知っている。\nアダム・レイナーはお前の旦那なんだろう？";
			link.l1.go = "FalseTrace_wife_10";
		break;
		
		case "FalseTrace_wife_10":
			dialog.text = "そうよ。私はこの化け物の妻なの。やっとこの悪夢が終わったと思っていたのに……あいつがあなたに私を捕まえさせたの？";
			link.l1 = "大体、その通りだった。アダムは俺に銀のことを嘘ついて、俺がフリュート船『"+pchar.questTemp.FalseTrace.ShipName+"「……間違いなく、あいつはお前を連れ戻すつもりだったぜ。四半刻ほど前に、俺に自分の行動を全部説明してくれたんだ。」";
			link.l1.go = "FalseTrace_wife_11";
		break;
		
		case "FalseTrace_wife_11":
			dialog.text = "「それで……あいつは何を望んでるんだ？何て言われた？」";
			link.l1 = "彼は正妻に自分の元へ戻ってほしいと思っている。俺を騙した償いとして、 片目のソリーの金についての情報を提供してくれるそうだ。そして俺はお前たち二人を連れて行くつもりだ\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+".";
			link.l1.go = "FalseTrace_wife_12";
		break;
		
		case "FalseTrace_wife_12":
			dialog.text = "いやだ……（泣きながら）あのろくでなしのところには戻りたくない！必死で逃げて足取りを隠したのに、結局見つかってしまった……悪党め！盗賊め！血も涙もない泥棒め！";
			link.l1 = "落ち着いて、カトリーヌ……言葉に気をつけなさい。彼はあなたの夫でしょう。それに、愛していると言っていたじゃないか。";
			link.l1.go = "FalseTrace_wife_13";
		break;
		
		case "FalseTrace_wife_13":
			dialog.text = "（泣きながら）私の夫？私の夫が誰か知ってるの？彼は元囚人で、前科者、そして今では最も残忍な盗賊なのよ\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.StartCity+"Gen")+"！あいつは下劣で汚い獣だ、俺のことなんて股の間の穴としか思ってねえんだよ！";
			link.l1 = "「彼と結婚する前に全部見てなかったのか？」";
			link.l1.go = "FalseTrace_wife_14";
		break;
		
		case "FalseTrace_wife_14":
			dialog.text = "最初は彼、違っていたのよ……それに、彼の過去も私にはとてもロマンチックに思えた……でも、結局すべてが変わってしまったの。もう彼の顔なんて見たくもないし、一緒に暮らすなんて絶対に無理、 わからないの？嫌なのよ！特に、彼が仕組んだあのフリュート船への襲撃の後じゃ、なおさら！";
			link.l1 = "ふむ……さて、どうしてやろうか、お嬢さん？";
			link.l1.go = "FalseTrace_wife_15";
		break;
		
		case "FalseTrace_wife_15"://ноды пересечения - конец
			if (CheckAttribute(pchar, "questTemp.FalseTrace.KillCaptain"))
			{
				dialog.text = "どうすればいい？私には分かっているわ。あなたは罪の道具よ、私の夫のせいでね。あなたは無実の男を殺した、 私に優しくしてくれた唯一の人を。罪を償いなさい、船長。アダムを殺して。私の目の前で。 このクズが死ぬところを見たい、死体に唾を吐きかけてやりたいの\nあいつが死んだら、奴の宝の隠し場所を教えてあげる。あの酔っ払いバカ、一度だけ私に隠し場所を話したのよ、はは、 本人はもう覚えてもいないくせに！";
				link.l1 = "へっ！カトリーヌ、お前は本当に冷たい女だな、俺にはわかるぜ！";
				link.l1.go = "FalseTrace_wife_16";
			}
			else
			{
				dialog.text = ""+pchar.questTemp.FalseTrace.CapName+"…フリュート船の船長だよ。あんたが彼を閉じ込めたんだ。頼む、彼と話してくれ！俺たちの命と自由のために、 きっと何か提案してくれるはずだ！何か考えを出してくれる！俺は…俺はもうアダムのもとには戻りたくない、これからは\n "+pchar.questTemp.FalseTrace.CapName+" 「私の夫よ！お願いです――アダム、あの化け物のところには戻さないでください！」";
				link.l1 = "ふむ。面白いな。で、俺の囚人が一体何を差し出せるってんだ？当局から身代金はもらえるし、 しかも斜視のソリーの金も手に入るんだぜ……";
				link.l1.go = "FalseTrace_wife_21";
			}
		break;
		
		case "FalseTrace_wife_16":
			dialog.text = "誰が残酷さについて語ってるんだよ。向かう先は "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity)+"、アダムの言う通りにしろ。ただし港じゃなくて一番近い入り江に上陸するんだ。俺たち三人がそこへ行くから、 お前はあの野郎を殺せ\n終わったら隠し場所を教えてやる。嘘じゃねえ、誓うぜ。お前はアダムより俺の言葉を信じてくれるだろ？あいつ、 一度お前を騙したじゃねえか。どうだ、船長？";
			link.l1 = "ああ……夫婦は似た者同士ってのは本当だな。カトリーヌ、お前を見てるとアダムにはお前が一番お似合いだって思うぜ……そんなにあいつを殺したいなら、酔っ払って寝てる間に刺しちまえばいいじゃねえか……\nボースン！こいつを連れて行け！";
			link.l1.go = "FalseTrace_wife_17";
			link.l2 = "俺は、自分を騙して利用しようとする悪党どもが大嫌いだ。よし、キャサリン、お前の提案を受けてやる。 アダムが信用できねえのは明らかだからな。だがな、もしお前も俺を裏切ったら、 ヨーロッパのどこにいようが必ず見つけ出して、頭に鉛玉をぶち込んでやる。\nさあ、とっとと失せろ。ボースン！こいつを連れて行け！";
			link.l2.go = "FalseTrace_wife_19";
		break;
		
		case "FalseTrace_wife_17":
			dialog.text = "これを後悔するぞ……誓う、俺は……";
			link.l1 = "ボースン！あいつを見張って、俺たちが到着するまで絶対に目を離すなよ\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
		break;
		
		case "FalseTrace_wife_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "6");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForSolly");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_19":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "7");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity));
			AddDialogExitQuestFunction("SetCheckForKillAdam");
			chrDisableReloadToLocation = false;
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;
		
		case "FalseTrace_wife_20":
			dialog.text = "何のことだ？俺たちをどうするつもりだ？なぜ俺たちの船を拿捕したんだ？";
			link.l1 = "俺に一言しゃべらせる気はあるのか、それとも俺の甲板長に命じてお前の口を猿轡で塞がせようか！？";
			link.l1.go = "FalseTrace_wife_8";
		break;
		
		case "FalseTrace_wife_21":
			dialog.text = "ソリーの金？本当にあの悪党を信じるのか？また騙されるぜ、あいつはそういう奴だ！囚人と話してみろ！\n"+pchar.questTemp.FalseTrace.CapName+" 本物の紳士だ、約束は絶対に破らないし、君に嘘もつかないぜ！";
			link.l1 = "あんたには説得されなかったぜ、お嬢さん。あんたの船長と話すことなんて何もねえ。あいつからは身代金をもらうし、 アダムからはソリーの金も受け取るつもりだ。もしまたアダムが俺を騙したら、地の果てまで追いかけてやる。 その時は自分が生まれたことを呪うことになるだろう……\nボースン！こいつを連れて行け！";
			link.l1.go = "FalseTrace_wife_23";
			link.l2 = "正直に言うと、俺はアダムを信用してねえ……操られるのは大嫌いだ。よし、お前の船長と話して、何を聞き出せるか確かめてみるさ。もう行っていいぞ……ボースン！こいつを連れて行け！";
			link.l2.go = "FalseTrace_wife_24";
		break;
		
		case "FalseTrace_wife_23":
			dialog.text = "お前は残酷で無慈悲な男だ！誓って俺は……";
			link.l1 = "「ボースン！こいつを見張って、俺たちが"+到着地+"に着くまでずっと目を離すなよ」 "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.QuestCity+"Gen")+"!";
			link.l1.go = "FalseTrace_wife_18";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_24":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			AddQuestRecord("FalseTrace", "8");
			chrDisableReloadToLocation = false;
			pchar.questTemp.FalseTrace.Prisoner = "true";
			SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], true);
		break;
		
		case "FalseTrace_wife_25":
			dialog.text = "もう終わった……かわいそうな "+pchar.questTemp.FalseTrace.CapName+" 仇は討たれたし、これでやっと胸を張って未亡人と名乗れるわ……";
			link.l1 = "俺は約束を果たしたぜ、カテリーヌ。今度はお前の番だ。";
			link.l1.go = "FalseTrace_wife_26";
		break;
		
		case "FalseTrace_wife_26":
			dialog.text = "もちろんです、船長。私の夫――今はありがたいことに元夫ですが――はご存知の通り盗賊でした。捜索を恐れて、奪った戦利品は家に置かず、隠し場所を作っていました――でも一度だけそのことを漏らしたことがあるんです。それでも、とても巧妙に隠していました――その場所には岸からは辿り着けません。";
			link.l1 = "とても興味深いな……で、それはどこにあるんだ？";
			link.l1.go = "FalseTrace_wife_27";
		break;
		
		case "FalseTrace_wife_27":
			dialog.text = "イスパニョーラ近くの小島で。\n灯台の中だ。";
			link.l1 = "ポルトープランス灯台だ！島にあるぞ！";
			link.l1.go = "FalseTrace_wife_28";
		break;
		
		case "FalseTrace_wife_28":
			dialog.text = "たぶんそうだな。そこに戦利品が見つかるはずだぜ。見てみな。以上だ。じゃあな、船長。";
			link.l1 = "待ってくれ……カトリーヌ、もし許せるなら、俺を許してくれ。お前の不幸の元凶が死んだことで、 少しでも心が癒されることを願っている。本当にすまない……";
			link.l1.go = "FalseTrace_wife_29";
		break;
		
		case "FalseTrace_wife_29":
			dialog.text = "俺はお前の同情なんていらねえ、船長。頼んだことはちゃんとやってくれたし、 お前が知りたがってたことも全部話しただろう。じゃあな……もう俺を悲しみと二人きりにしてくれ……";
			link.l1 = "じゃあな、Katherine。";
			link.l1.go = "FalseTrace_wife_30";
		break;
		
		case "FalseTrace_wife_30":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15);
			LAi_LocationDisableOfficersGen(pchar.questTemp.FalseTrace.QuestShore, false);//офицеров пускать
			//LAi_LocationDisableOfficersGen("Mayak7", true);//офицеров не пускать
			locations[FindLocation("Mayak7")].DisableEncounters = true;//энкаунтеры закрыть
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.quest.False_Trace_7.win_condition.l1 = "location";
			pchar.quest.False_Trace_7.win_condition.l1.location = "Mayak7";
			pchar.quest.False_Trace_7.function = "FalseTrace_AdamTreasure";
			AddQuestRecord("FalseTrace", "23");
		break;
		
		case "FalseTrace_wife_31":
			dialog.text = "汚ねえ野郎め！あいつは四人全員をやっちまいやがった！信じられねえ！";
			link.l1 = "こんな展開になるとは思わなかったか、カトリーヌ？俺はそう簡単には死なねえぜ。 二重の駆け引きもなかなか上手いじゃねえか！";
			link.l1.go = "FalseTrace_wife_32";
		break;
		
		case "FalseTrace_wife_32":
			dialog.text = "お前は俺の部下を殺したんだ。まさかこのまま生かしておくと思ったのか！？アダムの死で俺が満足するとでも？違う！ ここからは逃がさねえ。この島のすぐ近くに船がいる、お前のオンボロ船ごと沈めてやるさ！\nさあ、好きにしろよ。";
			link.l1 = "言ったでしょ、あなた、私を騙したら首が飛ぶって？ずる賢い悪党ね！死んだらもう少しはおとなしくなるでしょう。 この可愛い頭、今から鉛玉をお見舞いするわよ……";
			link.l1.go = "FalseTrace_wife_33";
			link.l2 = "かわいそうだな、カトリーヌ。復讐心に駆られた結果、結局お前のためにはならなかったな。 これからはお前の運命に任せる――この島に残ってもらうぜ。すぐに地元の漁師たちが見つけて、イスパニョーラまで連れていくだろう。\nそして、我々のすべての行いについて、主が裁きを下すことを願う……";
			link.l2.go = "FalseTrace_wife_35";
		break;
		
		case "FalseTrace_wife_33":
			dialog.text = "祈るべきはお前だ、化け物め！殺人鬼！助けてくれ！くそっ、や...";
			link.l1 = "もう十分聞いた。";
			link.l1.go = "FalseTrace_wife_34";
		break;
		
		case "FalseTrace_wife_34":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetImmortal(npchar, false);
			//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
			if(!CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE))
			{
				GiveItem2Character(pchar, "pistol1");
				EquipCharacterbyItem(pchar, "pistol1");
			}
			// <-- legendary edition
			LAi_ActorAnimation(pchar, "shot", "FalseTrace_CaterinaKilled", 1.0);
		break;
		
		case "FalseTrace_wife_35":
			dialog.text = "溺れてしまえ！お前の船が岩に打ち砕かれろ！お前なんか…";
			link.l1 = "じゃあな、Katherine。";
			link.l1.go = "FalseTrace_wife_36";
		break;
		
		case "FalseTrace_wife_36":
			DialogExit();
			sld = characterFromID("FalseTraceWife"); 
			sld.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "goto", "goto33", "none", "", "", "", -1);
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("Mayak7", false);//офицеров пускать
			locations[FindLocation("Mayak7")].DisableEncounters = false;//энкаунтеры открыть
			AddQuestRecord("FalseTrace", "25");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			OfficersReaction("good");
		break;
		
		case "FalseTrace_Bandits":
			dialog.text = "あ、ああ、こいつがアダムの殺し屋だ！キャサリンの言った通り、この野郎が隠し財産を奪いに来やがったんだ！";
			link.l1 = "「何だって？カトリーヌ？お前は誰だ？」";
			link.l1.go = "FalseTrace_Bandits_1";
		break;
		
		case "FalseTrace_Bandits_1":
			dialog.text = "俺たちが誰かって？俺たちはアダム・レイナーの仲間だ。お前に殺された男さ。あいつは俺たち兄弟団の頭だった。 今は俺が頭だ、名前は\n "+GetFullName(npchar)+"、それから俺の親分を殺したことと、親分の女房に暴力を振るったことの報いを受けてもらうぜ。";
			link.l1 = "暴力だと？何のことを言ってやがるんだ？";
			link.l1.go = "FalseTrace_Bandits_2";
		break;
		
		case "FalseTrace_Bandits_2":
			dialog.text = "アダムの背中を刺しやがって、この汚ねえ裏切り者め。お前はアダムが金をどこに隠したか、無理やり奥さんに吐かせて、 その哀れな女を見捨てて無人の浜に置き去りにしたんだろう。\nだが、あの女は生き延びた。俺たちに助けを求めてきて、あんたのやったことを正してくれってな。 何日もお前を待ってたぜ。そして今、ついに現れやがったな、この野郎！";
			link.l1 = "ハハッ！まさにカトリーヌらしいやり口だな……さて、よく聞けよ。アダムを殺したのは確かに俺だ。でもな、実はあいつの女房に頼まれてやったんだ。 女房の愛人が殺された復讐ってわけさ。報酬として隠し場所を教えてもらったんだ……";
			link.l1.go = "FalseTrace_Bandits_3";
		break;
		
		case "FalseTrace_Bandits_3":
			dialog.text = "貧しい未亡人を中傷するんじゃねえ、このクズ野郎！じゃあ、なんであの女が俺たちのところに来たんだ？ お前の命と引き換えに、金は全部俺たちが取れって申し出たんだぜ。あの女は金なんか欲しくねえ、 お前の死を望んでるんだ！旦那の死には正義の死で報いるってわけだ！\nだが誓って言う、あの女を貧乏のまま死なせやしねえ、俺の名にかけてこれは本当だ。 "+GetFullName(npchar)+"、そして今こそお前が死ぬ時だ、腰抜け野郎！";
			link.l1 = "なんてこった、見事な演説だな。おっと、あの女が来たぜ、この茶番を直に見たくてたまらねえんだろうな……旦那方？";
			link.l1.go = "FalseTrace_Bandits_4";
		break;
		
		case "FalseTrace_Bandits_4":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Adam_bandit_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_BanditsAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_Remove1":
			dialog.text = "お前は本当にドジだな、船長！銀でいっぱいのフリュート船を失うなんて……お前に期待したのが間違いだったぜ。じゃあな！";
			link.l1 = "さらばだ、アダム。";
			link.l1.go = "FalseTrace_Remove2";
		break;
		
		case "FalseTrace_Remove2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 15);
		break;
		
		case "FalseTrace_Remove_exit":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "FalseTraceWife_Remove", 15);
		break;
		
		case "FalseTrace_Remove2":
			dialog.text = "警告しただろう、船長、猶予はたった二週間しかなかったんだぜ！今ごろは、 片目のソリーがもう全部の戦利品を持っていっちまったはずだ。お前がそんなにドジなのは俺のせいじゃねえ。じゃあな！ ";
			link.l1 = "ああ、俺のせいだ。じゃあな、もう二度と会いたくねえぜ。お前といるとろくなことがねえからな。";
			link.l1.go = "FalseTrace_Remove_exit";
		break;
		
		case "FalseTrace_Solly":
			dialog.text = "へっ！やっとか！待ちくたびれたぜ、このクソ蚊どもも……\nあれ……ソリーはどこだ？どういうことだ……";
			link.l1 = "ソリーはここには来ねえ。俺があいつの代理だ……だからよ、金を渡すか、死にたいのか、どっちかだぜ。";
			link.l1.go = "FalseTrace_Solly_1";
		break;
		
		case "FalseTrace_Solly_1":
			dialog.text = "うおお！見てろよ！野郎ども、こっちへ来い！武器を取れ！";
			link.l1 = "こんな馬鹿げた死に方をするとはな。さあ来い、死肉漁りども！";
			link.l1.go = "FalseTrace_Solly_2";
			AddDialogExitQuestFunction("FalseTrace_SollyBonanzaAdd");
		break;
		
		case "FalseTrace_Solly_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			DialogExit();
			for (i=1; i<=6; i++)
			{
				sld = characterFromId("FTEnemy_crew_"+i);	
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FalseTrace_SollyAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "FalseTrace_GoldShip":
			dialog.text = "取引の約束を果たしてくれたな、船長。信じてくれて感謝するぜ。アダムのことは心配するな、 俺がしかるべき場所に連れていく。奴にはふさわしい報いが待ってるさ。";
			link.l1 = "アダムのことなんてどうでもいい。船についての約束はどうなったんだ？";
			link.l1.go = "FalseTrace_GoldShip_1";
		break;
		
		case "FalseTrace_GoldShip_1":
			if (sti(pchar.basenation == HOLLAND) || sti(pchar.basenation == SPAIN))
			{
				pchar.questTemp.FalseTrace.ShipNation = ENGLAND;
				pchar.questTemp.FalseTrace.ShipCity = "PortRoyal";
			}
			else
			{
				pchar.questTemp.FalseTrace.ShipNation = SPAIN;
				pchar.questTemp.FalseTrace.ShipCity = "Maracaibo";
			}
			dialog.text = "ああ、ああ、わかった。さて、今日から数えて……そうだな……12～14日後には\n "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" 金鉱石を満載した大型ガレオン船がヨーロッパへ向けて出航する。その護衛はフリゲートかコルベットが一隻だけだ\nだから、しっかり準備しろよ。あれは大きな獲物だが、侮れねえぜ。それでも、お前ならきっとやれるさ。 俺の抵抗もあっさり潰したくらいだからな……お前が目指すべきは "+XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen")+" 二週間後に待ち伏せの準備をしろ\n標的は護衛船一隻だけの重ガレオンだということを忘れるな。それだけだ、あとはお前の腕次第だぜ。";
			link.l1 = "なるほどな……さて、 "+pchar.questTemp.FalseTrace.CapName+"、さらばだ。カテリーヌと幸せな人生を送れるよう、幸運を祈るべきかな？二人が無事であることを願っている。 こんな悲しい状況で出会ってしまったのは残念だ。";
			link.l1.go = "FalseTrace_GoldShip_2";
		break;
		
		case "FalseTrace_GoldShip_2":
			dialog.text = "ありがとうございます、船長。前にも言いましたが、あなたにはどこか気品があります。 正直な行いが不名誉なものよりも多くの利益をもたらすと、いつか気づいてくれることを願っています。祖国に尽くせば、 きっと偉大な海軍士官になれるでしょう。";
			link.l1 = "お前の言葉、考えてみるぜ。さて、とりあえずこれでお別れだ！";
			link.l1.go = "FalseTrace_GoldShip_3";
		break;
		
		case "FalseTrace_GoldShip_3":
			DialogExit();
			locations[FindLocation(pchar.questTemp.FalseTrace.TargetShore)].DisableEncounters = false; //энкаутеры открыть
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "FalseTraceDouble_Remove", -1);
			pchar.quest.False_Trace_6.win_condition.l1 = "Timer";
			pchar.quest.False_Trace_6.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.False_Trace_6.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
			pchar.quest.False_Trace_6.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 14);
			pchar.quest.False_Trace_6.function = "CreateFalseTraceGoldShipOnMap";
			AddQuestRecord("FalseTrace", "19");
			AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony"+pchar.questTemp.FalseTrace.ShipCity+"Gen"));
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
