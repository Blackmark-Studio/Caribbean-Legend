// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("「どんな質問だ、」 "+GetSexPhrase("息子よ","娘よ")+"?","何でも聞いてくれ、聞いてるぜ…"),"聞いているぞ、今話せ。 "+GetSexPhrase("息子よ","娘よ")+"...","「三度目だが、」 "+GetSexPhrase("息子よ","娘よ")+"、必要なものがあれば言ってくれ。","「聖職者にはやることが山ほどあるんだ、あんたは俺の邪魔をしてるぞ」 "+GetSexPhrase("息子よ","娘よ")+"...","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は違うんだ、神父……"),"申し訳ないが、俺から言うことは何もねえ。","後で聞くぜ。すまねえな、神父。","失礼します、神父様……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "priest")
			{
				link.l1 = "失礼します、神父様。あなたの教区の聖職者の一人から、 ヨアヒム・メリマンが部屋を借りていた家を調査してほしいと頼まれたのですが……";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
		break;
		
		// калеуче
		case "caleuche":
			dialog.text = "どうだ？行ってきたのか、息子よ？";
			link.l1 = "あるぜ。しかし正直なところ、見なきゃよかったと思ってる。上の部屋ででっけえ斧を持った骸骨に襲われたんだ。 なんとか勝ったが、楽な戦いじゃなかったぜ。";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "主よ、我らの魂をお救いください！最悪の恐れが現実となってしまいました！";
			link.l1 = "それだけじゃありません、神父様。とうとう仕留めた時、そいつは女のような悲鳴を上げたんです。 骨を調べてみたら宝飾品が見つかりましたから、行方不明になっていた女将だったと考えて間違いないでしょう。";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "（十字を切る）……哀れな神の僕よ、主が彼女の魂に安らぎを与えんことを……";
			link.l1 = "メリマンは本当に魔術師らしいな。生きている人間をあんな化け物に変えるなんて、どうやったのか全く見当もつかねえ。 ";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "ヨアヒム・メリマンは非常に恐ろしい魔術師だ、息子よ。私がヨーロッパで彼を知っていた時は、 あんなことができるような男ではなかった。ここカリブ海で、彼は何か超自然的な力を得られるものを手に入れたのだ。";
			link.l1 = "「メリマンを知っていたのか、神父？」";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "そうだ、その通りだ。当時の私はリスボンの教区の一つで慎ましい神父をしていた。 ジョアキム・メリマンは裕福な貴族で、ある時から遠い国々 から船乗りが持ち帰った古い写本や巻物に興味を持つようになった。彼は錬金術の研究も始めたが、 しばらくして隠遁生活に入った。\n人々は彼の家で閃光を見たり、時には奇妙な臭いを嗅いだりした。そして夜になると墓地で彼の姿を見かけた。 ある時は新しい死体を掘り起こして自宅に運ぶのを目撃された。そしてついに我慢の限界が来て、 地元の修道院長が異端審問に連絡した。\n護衛たちがメリマンの家の扉を破った時、ジョアキムの姿はなかった――彼は秘密の抜け道から逃げていた。地下室には実験室があり、 歴戦の兵士たちですら目にしたものに衝撃と吐き気を覚えた。腐乱し切断された死体、人体や動物の骨、奇怪なものの数々 ……メリマンへの恐怖と憎悪はあまりにも強く、彼の家は瞬く間に取り壊された。\nメリマンは跡形もなく姿を消した。異端審問は彼の捜索を始め、不在のまま危険な魔術師として火あぶりの刑を宣告した。 しかし、彼はついに見つからなかった。そして今、長い年月を経て、 私は再びウィレムスタッドの街角で彼を目撃したのだ。";
			link.l1 = "「なぜ異端審問官たちに言わなかったんだ？」";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "息子よ、我々の教会が異端審問官と対立していることを知らないのか？ ヴィンチェント神父とその荒くれ者どもには近づきたくないんだ。";
			link.l1 = "わかりました。神父様、メリマンがどこから力を得ていたのか、私には心当たりがあります。やつは古代の遺物、 チャビン族のインディオたちが崇拝していた死の神ユム・シミルの翡翠の髑髏を手に入れたのです。";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "ふむ、メリマンは死体を使った魔術的な儀式や実験で知られていたから、それは本当かもしれん。\nこの恐ろしい男がウィレムスタッドを去り、彼がここに蒔こうとした悪魔の種をお前が滅ぼしてくれたこと、 神に感謝するぞ。\n我々はお前に大きな借りができた、息子よ。どうかこの聖別された品々を報酬として受け取ってくれ。";
			link.l1 = "ありがとうございます、神父様";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			Log_Info("You have received church amulets");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "amulet_2"); 
			GiveItem2Character(pchar, "amulet_6"); 
			GiveItem2Character(pchar, "amulet_8"); 
			GiveItem2Character(pchar, "amulet_10"); 
			ref sld = characterFromId("Havana_Priest");
			dialog.text = "しかし、それで我々の苦難が終わったわけではないのだ、息子よ。最近、私は手紙を受け取ったのだが\n "+sld.name+"、ハバナの教会の院長神父だ。恐ろしい知らせを持ってきた。キューバのジャングルの洞窟で、猟師たちが恐ろしい怪物――歩く死者を目撃したんだ。しかも最近、ジャングルに入った人々が行方不明になっていることを考えると、 なおさら不安だ。";
			link.l1 = "ふむ……これもメリマンの仕業だとでも言いたいのか？";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 30) link.l1.go = "caleuche_8_1";
			else link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			sld = characterFromId("Havana_Priest");
			dialog.text = "どう考えていいのかわからん、息子よ。しかし、あの黒い魔術師がそんなに力を持つようになったのなら、 諸島の住民全員が大きな危険にさらされておる。悪魔のしもべが何を企んでいるのか、神のみぞ知ることじゃ\nわしは 神父が…と願っておる "+sld.name+" 間違っていたが、とにかくハバナへ行って彼と話してくれ。\n君のために一ヶ月有効の通商許可証を用意しておいた。\nこれがあれば、ハバナの港に問題なく入港できるはずだ。";
			link.l1 = "わかった、神父。ハバナへ向かうぜ。";
			link.l1.go = "caleuche_9";
			npchar.quest.givelicence = true;
		break;
		
		case "caleuche_8_1":
			sld = characterFromId("Havana_Priest");
			dialog.text = "何を考えればいいのかわからん、息子よ。しかし、あの黒い魔術師がそこまで力をつけたのなら、 この諸島の住民全員が大きな危険にさらされている。悪魔の手先が何を企んでいるのか、神のみぞ知ることだ。\n私はただ、神父が "+sld.name+" 間違っていたが、まあいい――君にハバナへ行って、彼と話してきてほしいんだ。";
			link.l1 = "もちろんです、神父様。すぐにハバナへ向かいます。";
			link.l1.go = "caleuche_9";
		break;
		
		case "caleuche_9":
			dialog.text = "お前が教会の真の息子であることを嬉しく思うぞ。昼も夜もお前の健康と幸福のために祈ろう。わしの祝福と共に行け。 主がその邪悪なる力との戦いでお前を強めてくださるように。";
			link.l1 = "ありがとうございます、それではお別れです、神父様。";
			link.l1.go = "caleuche_10";
		break;
		
		case "caleuche_10":
			DialogExit();
			AddQuestRecord("Caleuche", "26");
			AddCharacterMaxHealth(pchar, 1);
			if (CheckAttribute(npchar, "quest.givelicence")) GiveNationLicence(HOLLAND, 30);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 3);
			ChangeCharacterNationReputation(pchar, HOLLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			pchar.questTemp.Caleuche = "havana";
			Caleuche_PrepareCubaGrot();
			AddLandQuestMark(characterFromId("Havana_Priest"), "questmarkmain");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
