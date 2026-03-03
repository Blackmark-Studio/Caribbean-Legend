// диалоги Уракана, Канека и прочих индейцев ица
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何かご用ですか？";
			link.l1 = "いいえ、何もありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// ица-горожане
		case "itza_ctz":
			dialog.text = LinkRandPhrase("また白い顔か……大神官はお前の心臓をえぐり取るのが楽しみだぞ……","青白い顔の者はテヤサルへの来方を知っているが、この街から出て行く者はいない！","驚いたぞ、色白の顔よ。まだ霊の国へ行っていないとはな……歩けるうちに歩いておけ、すぐに先祖たちに会うことになるぞ。");
			link.l1 = LinkRandPhrase("ほう、ほう。どうなるか見ものだな……","俺を脅かそうなんて思うなよ、赤い肌の戦士。そんなもんよりひどい目は何度も見てきたんだぜ。","さあ、さあ。子供たちを怖がらせてみろよ。");
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz";
		break;
		
		case "itza_ctz_1":
			dialog.text = LinkRandPhrase("「偉大なるカヴィルよ、我が敵との戦いに祝福を与えたまえ！」","偉大なるカヴィルと偉大なるククルカンが我々の前に姿を現してくださった。古代マヤでも、 こんなことは起きなかったぞ！","我々はククルカンとカヴィルの大いなる戦いの伝説を子供たちに語り継ぐのだ！");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "itza_ctz_1";
		break;
		
		// Уракан - вождь ица
		case "urakan":
			dialog.text = "お前は偉大な戦士だな、白い顔の者よ。俺たちはお前の血を神々に捧げる。お前は誇り高く死ぬのだ。";
			link.l1 = "落ち着け、赤い肌の戦士よ。俺はお前のカネクにククルカンや他の誰かへの生け贄として差し出されるつもりはねえぞ。 お前の戦士たちも俺を捕らえることはできなかった。奴らは一人残らず戦で倒れたんだ。";
			link.l1.go = "urakan_1";
		break;
		
		case "urakan_1":
			dialog.text = "ああ、お前は礼儀正しい戦士だな、白い顔の者よ。だが、タイアサル・イツァの戦士が何百人もいるのに、 お前一人では太刀打ちできぬ。だが、お前の言葉は興味深い。 どうして偉大なるカネクとククルカンのことを知っているのだ？";
			link.l1 = "さて、当ててみようか……お前はカネクじゃないから、名前はウラカンで、カネク神父の息子だろう？";
			link.l1.go = "urakan_2";
		break;
		
		case "urakan_2":
			dialog.text = "お前の唇は真実を語っているな、色白の顔よ。俺はウラカンだ、驚いたぜ。";
			link.l1 = "これを見たら、もっと驚くぞ……見ろ。";
			link.l1.go = "urakan_3";
		break;
		
		case "urakan_3":
			dialog.text = "ああ、神々よ！白い顔の者が仮面を持っているということは、時が来たということだ……お前こそククルカンが語っていた者だ。お前がタイアサルに来たら、彼のもとへ連れて行くよう命じられている。 彼はお前が来たことを知っている。";
			link.l1 = "ククルカン！？奴がタイアサルにいるのか？";
			link.l1.go = "urakan_4";
		break;
		
		case "urakan_4":
			dialog.text = "はい、白き戦士よ。ケツァルコアトルがタイアサルにやって来る。\nまもなく彼は祖先たちに光をもたらすために、マヤの偉大なる都市へと旅立つだろう。";
			link.l1 = "ちくしょう！もう奴はここにいるのか……（声をひそめて）ウラカン、お前のことは全部知ってるぞ。 クサトル・チャを真実の守護者と一緒にクソチェアテムとククルカンの仮面を探しに行かせたのはお前だってな……";
			link.l1.go = "urakan_5";
		break;
		
		case "urakan_5":
			dialog.text = "";
			link.l1 = "ウラカン族長、あなたの目には驚きと同時に疑念も見えますね。ククルカンのことが気に入らないのでしょう？";
			link.l1.go = "urakan_6";
		break;
		
		case "urakan_6":
			dialog.text = "イツァの戦士たちは皆、偉大なるククルカンが来たことを喜んでいる、白き戦士よ。\nお前はククルカンの前に立たねばならぬ。彼は幾夜もお前を待っていた。\n彼は偉大なる予言者だ。すべてを前もって知っている。\n飛翔する蛇のもとへ行け、それ以外の道はない。\n我らはお前がタヤサルを去ることを許さぬ。";
			link.l1 = "ククルカンが時の門を通り抜けた瞬間、お前も含めてここにいる全員が存在しなくなるってわからないのか？\nしかも一番面白いのは、お前たちは別の姿、別の体で生まれ変わるんだ……もしかしたらただの戦士か、あるいは不具者や物乞いとしてな。";
			link.l1.go = "urakan_7";
		break;
		
		case "urakan_7":
			dialog.text = "行け、色白の戦士よ。ククルカンはイツァ戦士たちの大神殿にいる。\n橋をまっすぐ渡って大きなピラミッドが見えるまで進め。\n神殿の下の扉から入り、聖域へ近づくのだ。";
			link.l1 = "わかった。ククルカンのもとへ行こう、どうやらこの対決からは逃れられそうにないからな。だが、警告はしたぞ。";
			link.l1.go = "urakan_8";
		break;
		
		case "urakan_8":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_warrior_SetStay(npchar, true);
			LAi_warrior_DialogEnable(npchar, true);
			NextDiag.CurrentNode = "urakan_9";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			AddQuestRecord("Tieyasal", "25");
			pchar.quest.Tieyasal_Templegreat.win_condition.l1 = "location";
			pchar.quest.Tieyasal_Templegreat.win_condition.l1.location = "Temple_great";
			pchar.quest.Tieyasal_Templegreat.function = "Tieyasal_InGreatTemple";
			// экспа за бой
			AddComplexSelfExpToScill(300, 300, 300, 300);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "urakan_9":
			dialog.text = "行け、白き戦士よ。ククルカンが待っているぞ。";
			link.l1 = "今向かっているところだ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_9";
		break;
		
		case "urakan_10":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "現実になった！お前がククルカンと戦う姿を見て、私はお前こそカビルその人だと確信した。 お前は私の父とククルカンのせいで死の危機に瀕したイツァの民を救うため、タイアサルに来たのだ。私の父、 大祭司カネクは、とうの昔に死んだマヤの祖先たちの名のもとにイツァの民を滅ぼそうとしている。\n私は長年イツァの民を守ってきた戦士長ウラカンだ。タイアサルから生きて出た青白い顔の者は一人もいない。 私と私の戦士たちは、イツァの民がこれからも長く守られ、生き続けられるよう努めてきた。 私は自分の民すべてを犠牲にしたくはない。";
			link.l1 = "それは知っていたぞ、ウラカン。だから橋の上で手を貸してくれと頼んだんだ。";
			link.l1.go = "urakan_11";
		break;
		
		case "urakan_11":
			dialog.text = "偉大なるカヴィルの目からは何も隠せぬ。ウラカンがあなたの本当の正体を見抜けなかったこと、お許しください。";
			link.l1 = "気にするなよ、親分。俺はククルカンの化身を倒したが、まだ大事な仕事が残ってる――過去への扉を閉じなきゃならねえ。この不自然な時の穴を封じる必要があるんだ。手を貸してくれるか？";
			link.l1.go = "urakan_12";
		break;
		
		case "urakan_12":
			dialog.text = "「ウラカンに何を手伝ってほしいんだ、カビルよ？」";
			link.l1 = "お前はクサトル・チャを真実の守護者と共に、クソチェアテムとククルカンの仮面を探しに行かせたな。つまり、 その仮面が時の門を閉じるために使えることを知っているわけだ。父上からそのことを聞いたのか？";
			link.l1.go = "urakan_13";
		break;
		
		case "urakan_13":
			dialog.text = "父は話さない。私は知識と叡智の神殿で書物を学ぶ。しかし、ウラカンには分からぬことが多い。 カヴィルなら理解できるかもしれぬ？";
			link.l1 = "一体何が分かったんだ？";
			link.l1.go = "urakan_14";
		break;
		
		case "urakan_14":
			dialog.text = "私はそれを暗記した。書かれているのはこうだ――「太陽が雨に逆らって昇り、炎が三角にその間に立つとき、トヒルの脚を脚に打ちつけ、 時の祭壇でククルカンの仮面を焼き尽くせ。そしてイツァムナの時の門を終末の日まで封じよ。」";
			link.l1 = "何だ。";
			link.l1.go = "urakan_15";
		break;
		
		case "urakan_15":
			dialog.text = "「はい。」";
			link.l1 = "イエスよ……門を見せてくれ。";
			link.l1.go = "urakan_16";
		break;
		
		case "urakan_16":
			dialog.text = "彼らはククルカン神殿にいる。\nだが、あそこの扉は閉ざされているんだ。開け閉めできるのは父だけだ。父がククルカン神殿の扉を開けるとき、 こう言うんだ。「太陽は昇り沈み、水は落ちて引き、火は燃えて消え、戦と平和は入れ替わる。しかし、 永遠なのは天だけ。時の上にあるのは、ただ天のみ。」";
			link.l1 = "面白いな……それを覚えておいて、何ができるか考えてみよう……";
			link.l1.go = "urakan_17";
		break;
		
		case "urakan_17":
			dialog.text = "私はここにいる、下の方、時の祭壇のそばだ。\nタイサルのあらゆるピラミッドや建物の内部をこの目で見てきた。\n鍵を見つけろ。\n私はここにいる。";
			link.l1 = "何か重要な質問があれば、必ずあなたのところに来ます。";
			link.l1.go = "urakan_18";
		break;
		
		case "urakan_18":
			DialogExit();
			NextDiag.CurrentNode = "urakan_adv";
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1 = "location";
			pchar.quest.Tieyasal_UrakanTemple.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Tieyasal_UrakanTemple.function = "Tieyasal_UrakanInTemple";
			AddQuestRecord("Tieyasal", "26");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "quest", "urakan", "", -1);
			// экспа за бой
			AddComplexSelfExpToScill(1000, 1000, 1000, 1000);
			AddCharacterExpToSkill(pchar, "Leadership", 3000);
			AddCharacterExpToSkill(pchar, "Fortune", 1500);
		break;
		
		case "urakan_adv":
			dialog.text = "ウラカンは偉大なるカビルに助言や行動で力を貸せるか？";
			if (Tieyasal_CheckTablets() && !CheckAttribute(npchar, "quest.tablets"))
			{
				link.l1 = "俺が見つけたこの石板を見てくれ。見つけた場所から考えると、お前の父親と何か関係があったに違いねえし、 どう見てもただの品じゃねえぞ…";
				link.l1.go = "tablets";
			}
			if (CheckAttribute(npchar, "quest.treasureentrance"))
			{
				link.l1 = "大神殿の頂上で別の入口を見つけたが、封印されている。どうやって中に入ればいいんだ？もしかしたら、 探しているものはあそこにあるのかもしれない。";
				link.l1.go = "treasure";
			}
			link.l9 = "今は何もない、ウラカン。自分で何とかするよ…";
			link.l9.go = "exit";
			NextDiag.TempNode = "urakan_adv";
		break;
		
		case "tablets":
			dialog.text = "神の石板だ。父上はいくつか異なる石板を持っていて、それはとても大切なものなんだ。古代タイアサルの建築者たちは、 この石板を使って隠された仕掛けを作動させたり、扉を開け閉めしたり、さらには魔法の儀式まで行っていたんだよ。\n正しい場所に置けば機能する――それが父上のやり方さ。でも、俺も君と同じ戦士だから、うまく使う方法は知らない。 カヴィルなら知っているかもしれないな？";
			link.l1 = "必ず真相を突き止めてみせる……";
			link.l1.go = "exit";
			npchar.quest.tablets = "true";
			NextDiag.TempNode = "urakan_adv";
			AddQuestRecord("Tieyasal", "31");
		break;
		
		case "treasure":
			dialog.text = "ここがタイアサルの財宝への扉だ。そこにはイツァ族インディオの富が眠っている。 扉を内側から開け閉めできるのは私の父だけだ。父なしで宝物庫に入る者などいない。私でさえもだ。";
			link.l1 = "「お前の父親はどうやって入口を開けたんだ？」";
			link.l1.go = "treasure_1";
		break;
		
		case "treasure_1":
			dialog.text = "父上はこうおっしゃっていました：「どんな財宝にも二つの側面がある。その両方を知る者だけが、 タイアサルの宝に入ることができる」と。\nこれが何を意味するのか、私には分かりません。カビルなら分かるかもしれませんね？";
			link.l1 = "これも何とかしてみせるさ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "urakan_adv";
			DeleteAttribute(npchar, "quest.treasureentrance");
			AddQuestRecord("Tieyasal", "32");
		break;
		
		case "urakan_19":
			PlaySound("Voice\English\Complete.wav");
			dialog.text = "やったぞ、偉大なるカヴィルよ！イッツァの民は今や安全だ。カネクの息子ウラカンである私が、 あなたから授かったこの名誉に決して恥じぬよう、 そして不名誉な白き顔の者どもによる侵略からタイアサルをあなたの名において必ず守ることを誓おう。";
			link.l1 = "よく分かるぜ、親分。さて、今は祝おうじゃねえか。俺たちはククルカンの裏切りの企みを阻止したんだ。 奴がもう二度と時の革命を起こすことはできねえさ。";
			link.l1.go = "urakan_20";
		break;
		
		case "urakan_20":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "偉大なるカヴィルに栄光あれ！私と私の世代にとって、タイアサルで二柱の神を目撃できたことは大いなる名誉である。\nこの歴史を我らの子孫のために記す。彼らはタイアサルでの神々の戦いを知るだろう！\nカヴィルに栄光あれ！栄光あれ！";
			link.l1 = "酒が欲しいな……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_Win_IndianBead");
		break;
		
		// Канек - жрец ица
		case "kanek":
			dialog.text = "お前は有翼の蛇、蒼白き顔よ。偉大なるククルカンの精霊が人の肉体に宿っているのだ。 お前がその化身の父を通じて彼の兄弟となったことは幸運だ――ちょうど私が、彼を産んだ女、すなわち彼の母の父であることが幸運であるように。それは大いなる名誉だ。おそらく、 それゆえにお前は強き戦士となり、今も生きているのだろう。\nだが、お前の時は尽きる、蒼白き顔よ。我らは新たな時代を始める、偉大なるマヤの時を。我ら自身の力を打ち立て、 二度と蒼白き顔どもをこの世界に入れはしない。まもなく。私、司祭カネクが行き、儀式を始める！";
			link.l1 = "「素晴らしい……」";
			link.l1.go = "kanek_1";
		break;
		
		case "kanek_1":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.7);
		break;
		
		case "kanek_2":
			dialog.text = "ウラカン、旦那の言葉を聞いただろう。今すぐ降伏しろ！";
			link.l1 = "偉大なる者たちが争う時、私たちのような凡人は遠くから見守るのが賢明でございます、お父様…";
			link.l1.go = "kanek_3";
		break;
		
		case "kanek_3":
			dialog.text = "「何だって！？しっかりしろ、息子よ！」";
			link.l1 = "この男はククルカンの兄弟であり、偉大な戦士だ。私は彼の中にカヴィルそのものの化身を見る！ あんな神に立ち向かえるのは、彼以外にいない。神々の決闘にぐずぐずしている暇はないぞ、父上！ そしてククルカンに供物を捧げれば、私の戦士たちはカヴィルに自らの血を捧げるだろう！\n";
			link.l1.go = "kanek_4";
		break;
		
		case "kanek_4":
			dialog.text = "「正気か、ウラカン？」";
			link.l1 = "長年にわたり、私はフラカンの名を受け継ぎ、カヴィルの名のもとに異国の侵略者から我らの土地を守り抜いてきた。 何百人もの敵が我らの棍棒の下に倒れ、タイアサルから生きて出た者はいない。だが、この蒼白い顔の戦士ほど強く、 素早い者は生涯見たことがない。もし彼がククルカンを打ち倒せるなら、彼こそカヴィルの精霊の化身に違いない！";
			link.l1.go = "kanek_5";
		break;
		
		case "kanek_5":
			DialogExit();
			sld = characterFromId("Mishelle");
			sld.dialog.currentnode = "kukulkan_win_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
