// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "明らかなバグだ。開発者に伝えてくれ。";
			link.l1 = "ああ、そうするよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "citizen":
			DelMapQuestMarkCity("Baster");
			LAi_SetImmortal(npchar, false);
			LAi_RemoveLoginTime(npchar);
			dialog.text = "やあ、船長！面白い商談があるんだが、どうだい。";
			link.l1 = "どうぞ、旦那。";
			link.l1.go = "citizen_1";
			DelLandQuestMark(npchar);
		break;
		
		case "citizen_1":
			dialog.text = "グアドループからスペイン領本土までの輸送の仕事でお前の船を雇いたいんだ。";
			link.l1 = "乗客としてそこへ行きたいのか？";
			link.l1.go = "citizen_2";
			link.l2 = "「スペイン領本土だと？俺は遠慮しとくぜ。スペイン野郎とは仲良くねえんだ。ほかの間抜けを探すんだな。」";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "おっしゃる通りです、船長。ただ、今回は危険な航海じゃありませんぜ。では、ごきげんよう。";
			link.l1 = "さらば。";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "承知しました、船長。ごきげんよう！";
			link.l1 = "さらば。";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "そうじゃないぜ、旦那。乗客ってのは船長の意のままになる男だろう？俺はあんたとあんたの乗組員、 それに船を雇いたいんだ。俺と友人二人をパナマまで連れて行ってほしいんだよ。";
			link.l1 = "パナマへ？どうやってだ？大陸をぐるっと回って航海するつもりか？";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "ハハハ！いい冗談だな、船長。もちろん違うぜ。お前がやることは、 俺たちをポルトベロからそう遠くないモスキート湾まで運ぶだけだ。\nパナマまでは自分たちで行くさ。ジャングルを抜けるのはこれが初めてじゃねえからな。";
			link.l1 = "支払いはどうするんだ？";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "ドゥブロン金貨の入った箱が二つ。三百枚だ。乗船したらまず一箱前金で渡す。目的地に着いたら、 もう一箱はお前のものだ。";
			link.l1 = "こんな簡単な仕事で太っ腹な報酬だな。裏があるんじゃねえのか、旦那？";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "船長、時間は金だぜ。俺たちには余裕がねえんだ。今夜ここを出航して、十日以内に目的地に着かなきゃならねえ。 これが二度目の契約だ。\nどうする、乗るのか？";
			link.l1 = "取引成立だ！";
			link.l1.go = "citizen_6";
			link.l2 = "申し訳ないが、旦那、あんたの提案は俺にはあまりにも胡散臭く聞こえるぜ。\n他の間抜けを探しな。";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "素晴らしい。今は仲間たちがジャングルにいるから、俺がこの取引のことを伝えておくぜ。 今夜十時にキャプスタービーチで待ってる。遅れるなよ、船長！";
			link.l1 = "「わかった。今夜十時、キャップスタービーチだ。」";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "ちょっと待ってくれ、船長、まだお互いに名乗ってもいないじゃねえか。俺の名はベルトラン・ピネットだ。で、お前は……";
			link.l1 = ""+GetFullName(pchar)+"。船長 "+GetFullName(pchar)+"。じゃあな、Pinette旦那。";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "OpenTheDoors", 20.0);
			npchar.location = "None";
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
		break;
		
		case "citizen_9":
			DelLandQuestMark(npchar);
			dialog.text = "Captain "+GetFullName(pchar)+"「おう、そこにいたか。出発してもいいか？」";
			link.l1 = "ああ。乗船を歓迎するぜ。";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "よし。前金としてドゥブロン金貨の詰まった箱を受け取れ。\nそれから忘れるな――目的地まで連れて行くのは十日以内だ。一日でも遅れたら許さんぞ！";
			link.l1 = "条件は覚えている。心配するな、間に合うぜ。席に着いてくれ。";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
			}
			else
			{
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			}
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "そうか、船長、約束の分はきっちり果たしてくれたな。今度は俺の番だ。 この箱と俺たちの心からの感謝を受け取ってくれ。";
			link.l1 = "取引できて光栄だぜ、旦那。";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "こちらこそ。それでは、"+pchar.name+"船長、さようなら "+GetFullName(pchar)+".";
			link.l1 = "さらば！";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
			//SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
			AddMapQuestMarkCity("baster", false);
		break;
		
		case "citizen_12a":
			dialog.text = "さて、船長、ここまで来たな。お前の取り決めの半分しか果たしてねえから、俺も同じようにするぜ。 前金はそのまま全額受け取っておけ。文句はねえだろうな？結局はお前のせいなんだからな。";
			link.l1 = "俺はこれが気に入らねえが、あんたの言うことは正しいと認めるぜ。\nここでお別れだな。";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "とにかく、奉仕に感謝するぜ、船長 "+GetFullName(pchar)+"。じゃあな！";
			link.l1 = "「さらばだ。」";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "おお！なんて偶然の出会いだ！ "+TimeGreeting()+", "+GetFullName(pchar)+"「！でも、どうしてだ？」";
			link.l1 = TimeGreeting()+"「ピネット旦那、見つけるのは簡単じゃなかったぜ。」";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "「それで、理由は何だ、船長？」";
			link.l1 = "旦那、という名の男がいるんだ "+GetFullName(sld)+" そして彼はあなたに会いたくてたまらないようです。\n理由はご存知でしょう。";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "もちろん知っているさ、でもね、親愛なる船長、 俺が旦那に会いたがっているわけじゃないってことも知っておいてくれよ\n "+GetFullName(sld)+" 全然だ。お前はあいつの賞金稼ぎか？俺にはさっぱり分からねえ。";
			link.l1 = "ああ、しかし今の俺はそういう身分なんだよ、しかも全然嬉しくねえ。俺が間違えちまって、今じゃ旦那 "+GetFullName(sld)+"くそっ、あいつのせいで選択を迫られたんだ。グアドループへのお前の華々しい帰還か、 あるいはドン・カルロス・デ・ミリヤルを解放しようとしたお前のちっぽけな企みの共犯として俺の首が飛ぶか、 どっちかだ。\nそれは俺には堪えるぜ、分かってるだろ。";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "ああ、あの野郎め！これは本当に卑劣な脅し方だな……。\nで、船長、どうするんだ？決断するのか、それともあんな奴に脅されっぱなしでいるのか？";
			link.l1 = "どう思う？俺はお前が俺と一緒にバステールへ来ると思ってるぜ。";
			link.l1.go = "citizen_19";
			link.l2 = "ここで俺に選択肢なんてあるのか？";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "ああ、残念ですが、船長。俺はあなたの美しい船に乗り込む気はないんだ。ここで力ずくで何かしようとしても無駄だぜ、 この場所は衛兵に囲まれてるし、もし乱暴な真似をすれば俺はすぐに助けを呼ぶからな。もちろん、 刺そうと思えばできるかもしれないが、俺たちの友人は冷たい死体からは一銭も受け取れやしない。だから、 今あなたが取るべき一番賢い選択は、俺に構わず立ち去ることだ。このまま無傷で帰してやるよ。";
			link.l1 = "本当に俺がこんなことがあった後で、黙って引き下がると思ってるのか？この騒動に巻き込んだのはお前だろうが、野郎、 そろそろケジメをつけてもらうぜ！";
			link.l1.go = "citizen_20";
			link.l2 = "まあ、確かにその通りだな。お前を刺すのは面白そうだが、意味がねえ。これで終わりだなんて思うなよ。 俺は今からバステールへ行く。そこで俺たちの仲間にお前の居場所を教えてやるさ。そしたら、 あいつは仮面をつけた連中をお前の元に送り込むだろう。\n";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "あ、ああっ！兵隊！助けてくれ！！！";
			link.l1 = "...";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "もちろんだ。お前の親分に、仮面の手下どもをちゃんと大人しくさせておけって伝えな。最近、 俺はずいぶん目立ってるからな。じゃあな、船長。";
			link.l1 = "...";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			DelLandQuestMark(npchar);
			dialog.text = "待ってくれ！降参だ！降参する！";
			link.l1 = "よし！さあ、武器を捨てて船まで歩け！";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "選択肢はいつだってあるんだぜ、船長。俺の理解では、あの銀行家からの脅しがなけりゃ、 あんたは俺を追い回したりしなかったんじゃねえか？";
			link.l1 = "「そのとおりだ。」";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "よし。じゃあ、あいつの口を確実に塞ぐ手を打ってやるぜ。お前が雇い主に持っていく手紙を書こう。 もしあいつが口を割るようなことがあれば、グアドループ総督が「カレッジ号」――大量のダイヤを運ぶ任務中だった運送ラガー――の失踪を企てて資金を出した男のことを知ることになる、と伝えてやれ。";
			link.l1 = "ふむ。だんだん分かってきた気がする、ピネット旦那。";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "さすが頭が切れるな、船長。もしコレージ号の失踪の真相を知ったら、 ド・リオンがあのずる賢い守銭奴の首を自ら城門に打ち付けるだろう。この手紙に、 脅迫者を黙らせる証拠を書き記すつもりだ。\nちょっと筆を取る時間をくれ。";
			link.l1 = "……わかった……";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "（書きながら）ほら、受け取れ。この包みの中には似たような手紙が二通入っている。一通は銀行家に渡してやれ、 あいつにも楽しませてやれ。もう一通は自分で持っておいて、しっかり隠しておけ。";
			link.l1 = " その情報は信頼できるのか？";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Baster", false);
			dialog.text = "誓うよ、お前さんは俺を助けてくれた、だから今度は俺が助けてやる。安心しな、 脅迫者はこの遺言状を読めばもうお前さんに手出ししねえさ。ああ、そうだ……もう一つだけ、船長。今回は穏便に済んだからな……俺の隠し財産があるんだ、今後俺の仕事に手を出さないって約束してくれるなら、その場所を教えてやるよ。 どうせグアドループにはもう二度と足を踏み入れられねえしな。";
			link.l1 = "手紙がうまく効けば、もちろん、それは俺が約束するぜ。";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "それで決まりだな。グアドループの洞窟の中、岩の間を探せ。お前の苦労へのささやかな報酬と思ってくれ。 幸運を祈るぜ、船長。";
			link.l1 = "「あなたもだ、ピネット旦那。」";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			DelMapQuestMarkCity("baster");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			dialog.text = "ごきげんよう、旦那！あなたが船長だ "+GetFullName(pchar)+"、合ってるか？";
			link.l1 = "その通りだ。何か用か？";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Monsieur "+GetFullName(pchar)+"、バステールの銀行主ができるだけ早く会いに来てほしいとあなたに頼んでいるんだ。あなたの到着を見逃さないように、 毎日港の事務所を確認するようにと命じられたよ。";
			link.l1 = "面白いな、で、なんであいつはそんなに俺に会いたがってるんだ？";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Monsieur "+GetFullName(sld)+" 直接理由を話してくれるそうだ。招待を断らないでくれよ。";
			link.l1 = "ふむ……まあいい。あいつら銀行家は権力者で、小物には時間なんざ割かねえからな。できるだけ早くその男に会いに行くぜ。";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "ありがとうございます、船長。ごきげんよう！";
			link.l1 = "さらば。";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "うおっ！このクズどもめ！こんなのが偶然の出会いなわけねえだろ……";
			link.l1 = "その通りだな、ジャン……いや、失礼、フアンだったな。お前を追い詰めたぜ。さあ、俺の貨物室に移動してくれないか？ ひと暴れしてから話そうじゃねえか。";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "俺は約束を果たしたぜ。今度はお前の番だ。やれよ、嘘をついたらどうなるか、よく覚えておけ。";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "バルバドスの本営プランテーションに行けば、ベルトラン・ピネットに会えるはずだ。\n彼はそこで事業を続けるつもりだったんだ。\nそのプランテーションの監督は彼の友人だぜ。";
			link.l1 = "どんな作戦だ？";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "グアドループでやってたのと同じだ。半分合法の取引、密輸、奴隷さ。奴は奴隷と砂糖の商売を狙ってるんだと思うぜ、 じゃなきゃ何でわざわざプランテーションに移ったんだ？";
			link.l1 = "なるほど。あいつはイギリス当局の中に後ろ盾がいるのか？";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "そうだと思うぜ。あいつは妙な奴だ。どこに行っても仲間がいるんだよな。";
			link.l1 = "他に何かあるか？";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "例えば何だ？ずる賢くて頭が切れる、何でも知ってるし、いつも切り札を隠し持ってるやつだ。 俺はあいつについてもっと知る時間があまりなかったんだ。";
			link.l1 = "了解だ。よし、俺はブリッジタウンへ向かわなきゃならねえ。お前はもう行っていいぜ、ドン・フアン。 ピネットに警告しようなんて考えるなよ。もしあいつがそこにいなかったら、またお前の首が危ねえからな。";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("bridgetown", false);
		break;
		
		case "killer":
			dialog.text = "悪いな、友よ。恨みはねえんだ。ただ、お前は知りすぎた。それが問題なんだよ。";
			link.l1 = "...";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза								  
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
