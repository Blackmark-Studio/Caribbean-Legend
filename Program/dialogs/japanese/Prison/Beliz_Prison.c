// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "話せ、聞いてやる";
			link.l1 = "俺の勘違いだった。じゃあな。";
			link.l1.go = "Exit";
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "start")
			{
				link.l1 = "ベリーズ周辺や町の中で盗賊や強盗団が活動していると聞いた。";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.Bandos") && pchar.questTemp.Caleuche.Bandos == "know" && CheckAttribute(pchar, "questTemp.Caleuche.belizbandos") && GetQuestPastDayParam("questTemp.Caleuche.belizbandos") < 3)
			{
				link.l1 = "その一味について情報を教えてやれるぜ。";
				link.l1.go = "caleuche_3";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche.BelizRegard"))
			{
				link.l1 = "あの一味の情報はどうだ？洞窟で奴らを捕まえたのか？";
				link.l1.go = "caleuche_7";
				DelLandQuestMark(npchar);
				DelLandQuestMarkToPhantom();
			}
			// Путеводная звезда ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz_Komendant"))
			{
				link.l1 = "町中が海賊の捕縛を祝っているようだな。詳しく教えてくれないか？";
				link.l1.go = "PZ_Beliz_Komendant_1";
				DeleteAttribute(pchar, "questTemp.PZ_Beliz_Komendant");
			}
			// <== Путеводная звезда
		break;
		
		// Путеводная звезда ==>
		case "PZ_Beliz_Komendant_1":
			dialog.text = "喜んでだ！こいつはただの海賊じゃねえ――あの悪党、マシュー・ラッターだ。";
			link.l1 = "誰だっていつかは運が尽きるもんだぜ。";
			link.l1.go = "PZ_Beliz_Komendant_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_Beliz_Komendant_2":
			dialog.text = "お前はイングランド人じゃねえし、商人にも見えねえから、あんまり興奮してねえのも分かるぜ。 ラターは何年もこの海域を荒らしまわってきたんだ、俺たちもドンたちも襲われたが、特に俺たちが狙われてきた。 あいつはいつも沿岸警備隊をうまくかわして、シーガルってコルベットで逃げてたんだ。 あの船はかつて諸島で一番速かったんだぜ。どうやってあんな軍艦を手に入れたのか、神のみぞ知るってやつだな。";
			link.l1 = "商人に負けたって本当か？しかもコルベットで？信じられねえ話だな。";
			link.l1.go = "PZ_Beliz_Komendant_3";
		break;
		
		case "PZ_Beliz_Komendant_3":
			dialog.text = "奇妙に聞こえるかもしれねえが、本当の話だ。しかも商人で、スペイン野郎だぜ！ 我が海軍もあいつから学ぶことがありそうだ。ソッタ船長は逃げ場がねえと悟って、戦闘の準備をしたんだ……";
			link.l1 = "このソッタ、なかなか変わった奴だな。";
			link.l1.go = "PZ_Beliz_Komendant_4";
		break;
		
		case "PZ_Beliz_Komendant_4":
			dialog.text = "たぶんそうだろう。奴はできる限り多くの貨物を積めるように船を改造したせいで、逃げることができなかった。 海賊が貨物を狙っていると知って、漂流しているふりをしたんだ。そして……";
			link.l1 = "…ちゃんとした時に帆を上げたのか？";
			link.l1.go = "PZ_Beliz_Komendant_5";
			if (!CharacterIsHere("Longway"))
			{
				sld = CharacterFromID("Longway");
				ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
			}
		break;
		
		case "PZ_Beliz_Komendant_5":
			dialog.text = "はっ！いや、ラッターが近づいたとき、あいつは至近距離でブドウ弾をぶっ放してから、 自分でその海賊船に乗り込んだんだ！ラッターが誰かを知ると、すぐに俺たちに引き渡した。まさに英雄、 名誉ある男だぜ！";
			link.l1 = "奴を突き動かしていたのは名誉だけじゃねえ――きっと「ウィンドバッグ」を捕まえた報酬があったはずだ。";
			link.l1.go = "PZ_Beliz_Komendant_6";
		break;
		
		case "PZ_Beliz_Komendant_6":
			dialog.text = "時には利益と善意が一致することもある。だが、そうだ、彼は十分な報酬を受け取ったぞ。\n閣下は彼が出航する前に、我が街の感謝の印として高価な品々をたんまりと持たせてやったんだ。";
			link.l1 = "あいつに会ってみたかったな―握手してみたいぜ。教えてくれ…";
			link.l1.go = "PZ_Beliz_Komendant_7";
		break;
		
		case "PZ_Beliz_Komendant_7":
			StartInstantDialog("Longway", "PZ_Beliz_Komendant_8", "Quest\CompanionQuests\Longway.c");
		break;
		// <== Путеводная звезда
		
		// Калеуче
		case "caleuche":
			dialog.text = "お前の情報源は本当のことを言っていた。あの盗賊どもは俺たちにとって本当に厄介な存在になっているんだ。 やつらについて何か話したいことがあるのか？";
			link.l1 = "それ以外には、奴らに俺の大事なものを一つ盗まれただけだ。本当は、 あんたが奴らについて何か知ってるんじゃねえかと思ってたんだ。もしかしたら、 誰か捕まって証言する気になってるかもしれねえ…";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "がっかりさせて悪いな、船長。でも奴らについては何も情報がねえ。わかってるのは、どこかジャングルに隠れていて、 町にも仲間がいるってことだけだ。それだけさ。\nもし新しいことがわかったら、すぐに俺に知らせてくれよ。";
			link.l1 = "わかったぜ、役人。そうするよ。";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			DialogExit();
			AddQuestRecord("Caleuche", "10");
			pchar.questTemp.Caleuche.Bandos = "seek";
		break;
		
		case "caleuche_3":
			string sTime;
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 0) sTime = "in three days";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 1) sTime = "on the day after tomorrow";
			if (GetQuestPastDayParam("questTemp.Caleuche.belizbandos") == 2) sTime = "tomorrow";
			dialog.text = "本気か、船長？話してみろ、耳を傾けてやる。";
			link.l1 = "町で奴らの密告者を見つけたぜ。そいつが言うには、 奴らの一味がチェトゥマルの入り江に到着する予定の船を襲う準備をしているらしい。悪党どもが集まっている\n "+sTime+" 夜、ベリーズの近くの洞窟のそばだ。\nそこに行くには、ジャングルの分かれ道で左の道を進めばいい。";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "洞窟にいるのか？それは素晴らしい知らせだ。すぐにあの悪党どもに待ち伏せを仕掛けるよう命じよう。 もしお前の言う通りで、密告者の話が本当なら、奴らを捕まえてやる。そしてその後は、 総督にお前への褒美を願い出るつもりだ。";
			link.l1 = "ありがとう！終わったら会いに来るぜ。";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "わかった。それでいい。";
			link.l1 = "また会おうぜ、役人。";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			DialogExit();
			AddDialogExitQuestFunction("Caleuche_BelizComendantPrison");
		break;
		
		case "caleuche_7":
			if (sti(pchar.questTemp.Caleuche.BelizChance) < 3)
			{
				dialog.text = "俺たちはあの悪党どもに熱烈な歓迎を用意してやったぜ、ははは！あいつらのツラを見せてやりたかったな！ 首領も含めて全員捕まえたぞ！何人かは抵抗しようとしたが、うちの勇敢な兵士たちがきっちり片付けてやった。";
				link.l1 = "素晴らしい知らせだな、役人！これでベリーズの市民たちもようやく安眠できるだろう。";
				link.l1.go = "caleuche_12";
			}
			else
			{
				dialog.text = "ふむ……俺の兵士たちは一晩中洞窟で待機していたが、結局誰も現れなかったんだ。軍曹は完全にブチ切れてたぜ。 お前がまだ捕まってないのは幸いだな。";
				link.l1 = "くそっ！そんなはずはねえ！どの洞窟で待ち伏せしたんだ？二つあるんだぞ！";
				link.l1.go = "caleuche_8";
			}
		break;
		
		case "caleuche_8":
			dialog.text = "お前が言った場所だ。分かれ道の右側のところで……";
			link.l1 = "左側だ！分かれ道の左だぞ、この間抜けども！";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "「だが、確かにお前は『右へ』と言ったはずだ。」";
			link.l1 = "おお、我が主よ！左だ！俺は言っただろ、左へ！左へだ！奴らを逃がしやがって、お前のせいだぞ！";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			AddQuestRecord("Caleuche", "16");
			dialog.text = "だったら、あんたが小声で何かブツブツ言ったんだろう。俺の耳はいいんだぜ。";
			link.l1 = "わかった、役人。俺はもう言い争うつもりはねえ。助けてやりたかったが、 自分で自分を助けられねえ奴には手の出しようがねえんだ。じゃあな。";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizChance");
			DeleteAttribute(pchar, "questTemp.Caleuche.BelizRegard");
		break;
		
		case "caleuche_12":
			dialog.text = "お前があの盗賊団を壊滅させた件について総督に報告した。\nお前の貢献は高く評価され、俺に報酬を渡す許可が下りたぞ――金銭のボーナスと、記念の火縄銃だ。";
			link.l1 = "ありがとう！";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received an arquebus");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("Caleuche", "17");
			GiveItem2Character(pchar, "chest"); 
			GiveItem2Character(pchar, "mushket3"); 
			dialog.text = "ご苦労だったな、船長！お前みたいに律儀な市民ばかりだったら、とっくに犯罪なんざ根絶してたはずだぜ！幸運を祈る！ ";
			link.l1 = "さよなら、役人さん！任務での幸運を祈るぜ！";
			link.l1.go = "caleuche_11";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, ENGLAND, 8);
			AddCharacterExpToSkill(pchar, "Leadership", 300);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
