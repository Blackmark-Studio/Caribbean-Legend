// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ」 "+GetSexPhrase("息子よ","娘よ")+"?","何でも聞いてくれ、聞いてるぜ…"),"聞いているぞ、今話せ。 "+GetSexPhrase("息子よ","娘よ")+"...","「三度目だが、」 "+GetSexPhrase("息子よ","娘よ")+"、必要なものがあれば言ってくれ。","聖職者にはやることが山ほどあるんだ、あんたは俺の邪魔をしてるぞ。 "+GetSexPhrase("息子よ","娘よ")+"...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("気が変わった……","今は違うんだ、神父さん……"),"申し訳ないが、俺には何も言うことはない。","後で聞くぜ。すまねえな、神父。","失礼します、神父様……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana")
			{
				ref sld = characterFromId("Villemstad_Priest");
				link.l1 = "ごきげんよう、神父様。修道院長 "+sld.name+" ウィレムスタッド教会の者に頼まれて来たんだ。あんたはキューバの洞窟で奇妙な目撃談を話したそうだな。";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "havana1")
			{
				link.l1 = "ジャングルの洞窟を訪れました、神父様。";
				link.l1.go = "caleuche_4";
				DelLandQuestMark(npchar);
			}
		break;
		
		case "caleuche":
			dialog.text = "神に感謝するぜ、あいつがちゃんと耳を傾けてくれてよ！生ける死者の噂が俺の耳に入ったとたん、 すぐにサンティアゴの異端審問官ヴィンチェント神父閣下に知らせたんだ。調査すると約束してくれたが、 今のところ何の動きもねえ！神父閣下はもっと重要な用事があるんじゃねえかと心配だぜ…";
			link.l1 = "俺が自分で調べてみるぜ。だいたい、こんな噂なんて酔っぱらった猟師どもの戯言さ――だから異端審問官も本気にしちゃいねえんだ。俺がジャングルに入って、この目で確かめてくるぜ。";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "保証しよう、息子よ、それは極めて重要だ。その歩く死者について話してくれた男を、私は命を懸けて信じている。";
			link.l1 = "よし、それなら戦いの準備をしよう。もし邪悪な存在が本当に洞窟に巣食っているのなら、 この世から必ず浄化してみせる。";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "主の祝福と共に行け、息子よ！さあ、この聖別されたお守りを持っていきなさい。お前の使命の助けになるだろう。 さあ行け、悪の眷属を滅ぼすのだ！";
			link.l1 = "それまで、ごきげんよう、神父 "+npchar.name+"。終わり次第、すぐにあなたのところへ戻る。";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "27");
			pchar.questTemp.Caleuche = "cave";
			Log_Info("You have received a church amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_7"); 
			if (GetCharacterIndex("cavehunter") != -1)
			{
				sld = characterFromId("cavehunter");
				sld.dialog.currentnode = "cavehunter_5";
				LAi_SetGuardianType(sld);
				sld.protector = true;
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				AddLandQuestMark(sld, "questmarkmain");
			}
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1 = "location";
			pchar.quest.Caleuche_cuba_caveentrance.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.Caleuche_cuba_caveentrance.function = "Caleuche_CubaCaveEntrance";
		break;
		
		case "caleuche_4":
			dialog.text = "何を見たのだ、息子よ？我々の不安は杞憂だったのか？";
			link.l1 = "申し訳ありませんが、神父様、そうではありません "+npchar.name+"。洞窟にはアンデッドがうようよしていたが、神の助けを借りて俺は勝利したぜ。 もう奴らが誰かを悩ませることはないだろう。";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "主を讃えよ！まさにお前は神の懲罰の剣だ、息子よ！どうかハバナ教区全体を代表して心からの感謝を述べさせてくれ。\nどうぞ、この聖別されたお守りを感謝の印として受け取ってくれ。危険な旅路できっと役立つはずだ。";
			link.l1 = "ありがとうございます、神父様 "+npchar.name+".";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_3"); 
			GiveItem2Character(pchar, "amulet_9"); 
			GiveItem2Character(pchar, "obereg_7"); 
			GiveItem2Character(pchar, "obereg_11"); 
			dialog.text = "さらに、あなたの英雄的な行いを庶民にも貴族にも伝えるようにし、昼夜を問わずあなたのために絶えず祈り続けます。";
			link.l1 = "ありがとうございます、神父様。もう一つお聞きしたいことがあります。";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "「何でも聞きなさい、我が子よ。」";
			link.l1 = "「教えてくれ、神父」 "+npchar.name+"、最近ジョアキム・メリマンという名の男があなたの町に来たか？中年の旦那で、 口ひげとあごひげをたくわえたポルトガル人、鋭い目つきをしているんだが？";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Villemstad_Priest");
			dialog.text = "名前にも説明にも心当たりがない、すまない。誰なんだ、その男は？";
			link.l1 = "メリマンは魔術師だ。異端審問官たちはずっと長い間、彼を追っている。神父 "+sld.name+" そして、キューバで生ける屍が現れたのは奴の仕業だと俺は疑っている。 少し前まで奴はウィレムスタッドに住んでいたが、突然姿を消したんだ。\nその直後、奴を泊めていた女が歩く骸骨に変わっちまったんだ。";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "なんという悪夢だ！すぐに異端審問官たちに知らせる、ヴィンチェント神父ご本人にもだ！ここで何が起きているか、 彼が知らねばならん！教えてくれ、息子よ、ジャングルで行方不明になった人々は……どう思う？";
			link.l1 = "確かに、洞窟にいたあの生ける屍どもは、あんたの元市民だったに違いねえ。 俺はキューバでこのポルトガル野郎を探し出して、思い知らせてやるつもりだ！あの悪党は、 ユム・シミルの翡翠の頭蓋骨っていう古い異教徒の遺物を手に入れやがった。あの遺物とインディアンの呪術があれば、 誰も止めなきゃメリマンはもっと厄介なことを引き起こすだろうぜ。";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			dialog.text = "「アンデッドが再び蘇ると信じているのか？」";
			link.l1 = "ほぼ間違いないだろう。何が彼を突き動かしているのかは分からねえが、奴の野望が善良なものとは到底思えねえな。";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "全能なる神が我らを憐れんでくださるように！探し出しなさい、息子よ！聖なる教会の名のもとに、 彼に対してどんな手段を取ってもよいと許可する！すぐに使者をサンティアゴへ送り、 ヴィンチェント神父への報告を託そう。";
			link.l1 = "そうしてくれ。じゃあな、神父 "+npchar.name+".";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			DialogExit();
			AddQuestRecord("Caleuche", "29");
			pchar.questTemp.Caleuche = "graveyard";
			AddCharacterMaxHealth(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddLandQuestMark(characterFromId("Havana_CemeteryMan"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
