// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
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
			dialog.text = "明らかなバグだ。開発者に知らせてくれ。";
			link.l1 = "ああ、そうするよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"！おや、見違えたな、友よ、それにうまくやってるじゃねえか！お前の噂が立ち始めてるぜ、知ってるか？覚えが早いな、 旦那、俺は本当にお前を誇りに思うぜ。これからもますますの幸運を祈ってる！また会えて嬉しいぜ！";
				link.l1 = "グレゴワール・ヴァリニー司教様、なんという出会いでしょう！私のささやかな功績に多大なご恩をいただいております。 お会いできて光栄です！ご武運を！";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "「ああ」 "+GetFullName(pchar)+"！おい、様子が変わったな、相棒。それに、うまくやってるじゃねえか！お前の噂が立ち始めてるぜ、知ってるか？ 覚えが早いな、旦那。正直、俺はお前を誇りに思うぜ。";
				link.l1 = "グレゴワール・ヴァリニー旦那、なんてこった！俺のつまらねえ成功は全部あんたのおかげだぜ。お会いできて光栄だ！ さて、どうせまた何か商売の話でも持ってきたんじゃねえのか？";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "ああ、そうだぜ。手短に話すぞ、時間は金だからな。さて、 ブラジルからキュラソーへ戦略物資を積んで航行していたオランダ王冠艦隊が、 トリニダードと本土の間でイングランドに待ち伏せされたんだ。会社のフリュート船一隻だけが逃げ延びて、 ボカ・デ・ラ・セルピエンタ海岸に停泊した。積み荷の一部は救い出せたが、長くは持たなかった――現地のインディアン部族に襲われたんだ\n俺の情報によれば、あの海岸にいたオランダ人は全員皆殺しにされて、積み荷は部族の村に運ばれたらしい。 インディアンどもはオランダの火器も奪ったが、かなりの損害を受けた。今がチャンスだ！ あの辺りじゃイギリスとオランダがまだ戦っていて、失われたフリュート船なんか気にしてる暇はねえ。今のところはな……お前には船と乗組員がいる。俺たちでそこへ行って上陸し、インディアンどもを片付けるんだ。 積み荷はとんでもなく価値が高いし、量もたっぷりある\n偵察のために小隊を送り込んでおいた――それが俺の出せる精一杯だった、金がなくてな、覚えてるだろ？信頼できる買い手もいるし、 俺の剣と傭兵も頼りにしてくれていい。取り分は五分五分、一週間で現地に着くぞ。どうだ、相棒、乗るか？";
			link.l1 = "申し訳ないが、旦那、俺は遠慮しておくぜ。きつい航海を終えたばかりで、 修理や新しい仲間を集める時間も足りねえんだ。こんな神に見放された場所でも、欲しいもの全部は手に入らねえもんさ。 ";
			link.l1.go = "greguar_exit";
			link.l2 = "危険な仕事みたいだが、儲けも冒険もありそうじゃねえか。もちろん俺も乗るぜ！ぐずぐずしてる暇はねえ、 さっさと行こうぜ！";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "残念だな。まあ、お前が決めることだ。幸運を祈るぜ、旦那、俺はとにかくそこへ向かうつもりだ。 男ならやってみなきゃな？";
			link.l1 = "ご武運を、Valinnie様！";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "いい選択だな、相棒！ちょっと小遣いが欲しいんだろ？ところで、お前の兄貴は元気か？";
			link.l1 = "俺はいくらでも金が欲しいぜ。ミシェル？兄貴は元気で、暇を持て余してるんだ。たまに羨ましくなるよ……さあ、出航の時間だ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "楽勝だぜ！こいつらはオランダ人との小競り合いを生き延びた新米どもだ。俺たちはもっと内陸に進むべきだな、 俺の探検隊はきっとそこにいるはずだ！";
			link.l1 = "簡単すぎたようだが……まだ喜ぶのは早いぜ、Valinnie旦那。あそこを見てみろ……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "くそっ、あの赤ん坊どもめ！もう少しでやられるところだったぜ！ 今じゃ村には女と子どもしか残ってねえのは間違いねえ。出発するぞ！";
			link.l1 = "お前がマスケット銃のことを言ったかどうか、俺にはよく分からねえし、見てもいねえ……まあ、どうでもいい。行くぞ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "どういう意味だ？オランダ人と俺たちで全員ぶっ殺したってことか！";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "逃げるだと？頭がおかしいのか？もうすぐ目的地だぜ！化粧した野蛮人どもが怖いのか？";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "下の下だよ、船長。俺はヨーロッパに帰るぜ。がっかりだ！お前にも、この腰抜けどもにも、この血塗られた土地にもな！ ";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "ふう！やったぜ！";
			link.l1 = "「だが、どんな犠牲を払ったと思ってるんだ！見ろよ！俺たちの隊のほとんどが死んじまった。撤退すべきだ、 グレゴワール。まだ他にも戦士が待ち構えてる保証なんてどこにもねえ。それに、戦利品を運ぶ人数も足りてねえんだ。」 \n";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "くそっ！悲しいが、お前の言う通りだな、 "+pchar.name+"：たとえ野蛮人どもが全員死んでいたとしても、 オランダ人かイギリス人がここに上陸する前に積荷を運び出すことはできねえ。今すぐ出発するしかねえ！こんな忌々 しい海岸なんざ、くたばっちまえ！";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "ふう！やったな！よくやったぜ、 "+pchar.name+"「さあ、これからは野蛮人どもの巣へ賞品を取りに行くぜ！今や俺たちを止められるものは何もねえ！」";
			link.l1 = "イギリス野郎とオランダ野郎がまだ揉めてるうちに急いだ方がいいぜ。行くぞ！";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "うまくやったな "+pchar.name+"。あとは怪しまれずに積み荷を売るだけだ。信頼できる買い手がいるんだが、やつは真夜中にラマンタン湾で待っている。 \n士官は連れてくるな、それに会う前にその場所へ近づくのも避けろよ、客はかなり神経質な奴だからな。";
			link.l1 = "商売は商売だ。積み荷は売らなきゃならねえし、安全にやらなきゃポワンシーへの借金がもっと増えちまう。わかった、 真夜中までには行くぜ。";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "終わったぜ。荷は降ろしたし、依頼人も来てる。あとは俺たちが話をつけよう。";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "驚け、この野郎ども！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "ああ、ジョニー、なんて奴だ！最高だぜ！何か言いたいことはあるか、 "+pchar.name+"?";
			link.l1 = "いや、違う。いや、やっぱりそうだ！なんだと！？";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "死人をからかうんじゃねえ、旦那。礼儀ってもんがあるだろうが…金はここにあるし、積荷は俺と仲間たちがちゃんと管理してる。やつらを海岸には送っちゃいねえ、無駄になるだけだ。 特にジョニーを行かせるなんてな。あそこにいる、カルヴァリンを持った赤肌の奴が見えるか？ジョニーはな、 自分の部族のことが昔からあんまり好きじゃなかったんだよ。";
			link.l1 = "そうか……これからどうするんだ？俺も殺すつもりか？";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "まあ、そうすべきなんだろうが、俺は情に流されやすいんだ。\n出て行け、そして金の四分の一だけ持っていけ。\n積み荷と残りの金はここに置いていくんだ。\n英雄気取りはやめとけよ、ここは本土のジャングルじゃねえんだ。\nお前に勝ち目はないぜ。";
			link.l1 = "「それで貴族らしさや礼儀はどこへ行ったんだ、グレゴワール？お前からこんな態度は期待してなかったぞ。私は行くが、 このことは忘れないからな。」";
			link.l1.go = "greguar_23";
			link.l2 = "俺は英雄ごっこなんかしてねえ、最初からな。単にお前ら全員ぶっ殺すだけだ！まずはこの女たち、 次にあのグレネードランチャー持った猿、そして最後はお前だ！";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "この浜辺には貴族も悪党もいません、旦那。いるのは五人の男と大砲一門、そして犠牲者だけです。 ここではこんなことがよく起こりますが、あんたは唯一正しい選択をした。見事だ。\nところで知っていますか？あんたの代わりに、今ここに立っているのが他の二人だったかもしれないんですよ。 彼らはほとんどあんたと同じようなものです。でも、ここにいるのはあんたで、彼らじゃない。そしてそのせいで、 きっと彼らは滅びるでしょう。";
			link.l1 = "よくわからねえな……";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "いつか分かる日が来るだろう。奴らは最後の教訓を受けなかったが、お前は受けた。どういたしまして。さらばだ、旦那。 カリブへようこそ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "ああ……お前は今まで教えた中で一番出来の悪い弟子だな。まあいい……人それぞれってやつだ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "ちょうどいいタイミングだぜ！俺たちはカリブ族の大群からかろうじて逃げてきたんだが、 奴らはお前の方に向かってたみたいだな。見たところ、もう遭遇したようじゃねえか。奴らの村はすぐ近くだが、 俺たちの問題はまだ始まったばかりだぜ。";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = ""+GetFullName(pchar)+"「！お前がここにいるとはな！まったく驚かねえぜ！ちょうどいいタイミングだ、相棒。 俺たちはカリブの野郎どもの大群からかろうじて逃げてきたんだが、あいつらはお前の方に向かってたぞ。見たところ、 もう会っちまったみてえだな。」";
			link.l1 = "繁盛してるか！それにしても驚いたぜ！またインディアンに穴でも開けてきたのか？セリーナは元気か？";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "この遠征に参加したのは愚かだったな。\n娘がもう一度俺に会える日が来るのか、考えてしまうよ。\nセリーナか？あいつは家でお前のことを夢見て座ってるさ！\nマルティニークの若者たちは、もうすっかり希望を失っちまった……\nだがな、このマスケット銃を買ったことは今では後悔してないぜ。頑丈な火器だ。信頼できる。\nそれに、また自殺みたいな任務に参加する理由が一つ増えたってわけだが、お前が来てくれたおかげで、 少しは死ににくくなったな。\nあいつらの村はすぐ近くだが、俺たちの問題はこれからが本番だぜ。";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "全員じゃねえ。俺たちの斥候は撃たれたが、なんとか奴らの巣までたどり着いた。 酋長本人が護衛を連れてここに来るらしい。しかも奴ら、オランダ製のマスケット銃を持ってやがる。数でも有利だし、 怒り狂ってるぜ。酋長は部族一の戦士で、手下どもはまるで悪魔みてえな連中だ。今すぐここで決断しなきゃならねえ。 戦うか、逃げるかだ。俺は正直、後者を選びてえがな……\n";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "あんたはまだ奴らを見てねえんだよ、旦那！あの「野蛮人」どもは火縄銃を持ってやがるし、 しかも驚くほどうまく扱いやがるんだ。誰かが奴らに使い方を教えてやがるのは間違いねえ！ だからもう一度でも俺のことを腰抜け呼ばわりすんじゃねえぞ！";
			link.l1 = "落ち着いてどうするか決めよう。まだ時間はある。";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "聞いてるぜ "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				Notification_Skill(true, 31, SKILL_SNEAK);
				link.l1 = "やるぞ、野郎ども！この丘の向こうには貨物と金があるんだ！俺たちはそれを手に入れるためにここに来たんだ、 絶対に引き下がらねえ。インディアンの連中が火縄銃持ってようが、俺たちを止められるわけねえだろ！ あいつらをぶっ倒して、仕事を終わらせるぞ！人数も十分いる、待ち伏せのチャンスだ。四人が側面から火を浴びせて、 残りはここで構える。数を減らして、とどめを刺すんだ！";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (GetCharacterSkill(pchar, SKILL_SNEAK) < 31) Notification_Skill(false, 31, SKILL_SNEAK);
				if (n < 3) notification("Not enough people", "X");
				if (n > 0)
				{
					link.l1 = "やってやるぞ、野郎ども！この丘の向こうには獲物と金があるんだ！俺たちはそれを手に入れるために来たんだ、 絶対に引き下がらねえ。マスケットを持ったインディアンどもなんかに止められてたまるか！奴らをぶっ殺して、 仕事を終わらせるぞ！";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "俺たちにはあらゆる面で不利だぜ。\nすぐ後ろにオランダ野郎がいることを忘れるなよ。";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "俺たちは生きて帰ってきたぜ！もう冒険は十分だ……少なくとも数か月はな、はは！娘のところに行かねえとな。ぜひ遊びに来てくれよ、 "+pchar.name+"。どうか、お気をつけてください。";
			link.l1 = "約束はできねえぜ、プロスパー。幸運を祈る！";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "俺は警告しただろう、船長、気をつけろってな！この野郎には怪しいところがあると思ってたんだ。";
			link.l1 = "繁栄を！ありがとう！でも、どうやって？";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Poor lad, even though he was a pirate.";
			dialog.text = "ジョニーがやたらと喋りすぎたんだ。砂浜にいたあの赤い肌の奴さ。あいつ、娼館に来て女を引っ掛けようとしたんだが、 相手にされなかった。それでジョニーが激怒してな、「もうすぐ金持ちになるんだ、 仲間と一緒にジャングルである船長を殺すからな！」って大声で喚き始めたんだ。こりゃまずいと思って、 町でもちょっと名を上げてたお前さんの士官のところに走ったってわけさ。 "+sTemp+" 「お前には大きな借りがあるぜ」 "+pchar.name+"、だからあまり感謝されなくてもいいんだ。";
			link.l1 = "それでも、本当にありがとう、プロスペル！ここはきつかった……本当にきつかったぜ。俺のクルーに入らないか？お前みたいな士官が必要なんだ。最近は忠実な奴を見つけるのは難しい、 特に腕の立つ射撃手はな。";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "いや、友よ。俺には娘への責任があるんだ。娘に冒険はもうやめるって誓わされたんだよ。あれが最後の冒険だった。 くそっ、残念だが、俺はこの世で何よりも娘を愛してるんだ。じゃあな、\n "+pchar.name+"。それに……セリナはいつもあなたのことを話しているんだ。いつか遊びに来てくれないか？";
			link.l1 = "誰にもわからねえ、もしかしたらそうするかもな……じゃあな、プロスパー！お前の娘さんにいい婿が見つかるといいな……（独り言）教訓だ、グレゴワール旦那、教訓だ……人それぞれってやつだな……このことは忘れねえぜ。";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "「てめえ、何者だ？」";
			link.l1 = "荷は手に入れた。興味あるか？";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "はっ。すごく興味があるぜ。特に俺の依頼人がな。で、取り分はどうなってる？";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" 鉄木の "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" 船シルクの "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" 縄と "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" 樹脂の。";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "よし。鉄木は一つにつき2200ペソ、樹脂は900ペソ、船用絹は1600ペソ、ロープは1000ペソだ。\nさて、ここには何があるかな……ほう、ほう。 "+iTotalTemp+" ペソだ。どうだ？";
			link.l1 = "「取引成立だ！」";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "素晴らしい！もっと持ってこい。オランダ人はいつもインディアンに気前がいいな……で、こいつらは誰だ？なんだと！？";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "ああ、船長。理由があって出航前に飲みすぎちまったんだ。";
			link.l1 = "お前か？どうして！？";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "すまねえ、船長。インディアンとのゴタゴタの後で、一杯か二杯やらずにいられなかったんだ。女がいてな、 百ペソ払って部屋を取ったら、そいつが…そいつが…";
			link.l1 = "「何？盗まれたのか？」";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "いやだ！あいつは惚れちまったんだ！くそっ、あの場から逃げりゃよかったぜ！でもよ、お前の友達が現れて、このクズ――お前の元仲間――が、お前を抱いて殺そうとしてるって俺に怒鳴りやがったんだ。";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "よくやったな、プロスパー…";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "プロスペール……本当にすまない。あなたの娘さんの面倒は俺が見る。教訓になったぜ、グレゴワール旦那……なんだって？人それぞれだと？覚えておくぜ。";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "行きましょうか、船長？";
			link.l1 = "ああ。ご苦労だったな。酒には近づくなよ、そうすりゃあの美女からも助けてやるぜ。行くぞ。";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
