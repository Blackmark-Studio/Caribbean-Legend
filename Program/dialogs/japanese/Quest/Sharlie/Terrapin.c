// НПС по квесту Суп из черепахи
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "いいえ、何もありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// денщик Фокса - Бенджамин Джонс
		case "BenjaminJons":
			if (CheckAttribute(PChar, "questTemp.Terrapin.Benjamin") && pchar.questTemp.Terrapin == "baster")
			{
				dialog.text = "只今、大佐閣下は軍事演習で野外に出ておられます。船長、何のご用でしょうか？";
				link.l1 = "今回はお前が必要なんだ、ベン。妹のモリーについて悪い知らせがある。 あの美しい娘がどうやら厄介なことに巻き込まれているらしい。トルトゥーガの海賊に捕まってしまったんだ。 彼女は助けを求めていて、俺にお前へ警告するよう頼んできた。その伝言を届けようとした男は殺されたが、 死ぬ前にお前の妹のことを俺に伝えてくれた。";
				link.l1.go = "sister";
				break;
			}
			sld = characterFromId("Fox");
			if (sld.location == pchar.location)
			{
				dialog.text = "フォックス大佐に会いに来たのなら、中へどうぞ——彼が応対してくれるぞ。";
				link.l1 = "「よろしい、そうしよう。」";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "大佐はここにいない。後でまた来てくれ。";
				link.l1 = "「よし……」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "BenjaminJons";
		break;
		
		case "sister":
			dialog.text = "ははっ！お前は俺の妹を「美人」と呼んだ初めての男だぜ。神様はあいつに擲弾兵みたいな体と、 声の代わりにエリコのラッパを授けたんだ。うちのモリーは自分の身は自分で守れるが、 主の創造力は首から下だけじゃ終わらなかった。いやいや、一番すごいのは、 亡くなった親父の毛むくじゃらであばただらけの面を、あいつの胸の上にくっつけたことさ。正直言ってな、旦那、 親父のツラは馬ですら気絶させる代物だったんだぜ。";
			link.l1 = "あまり動揺していないようだな……";
			link.l1.go = "sister_1";
		break;
		
		case "sister_1":
			dialog.text = "それで、なぜ彼女がトルトゥーガに現れるんだ？モリーは我らが勇敢な大佐の娘、キャサリン・フォックス嬢の召使いだ。 キャサリン嬢は父親の誕生日を祝うためにヨーロッパからやって来る予定だったんだが、 彼女の乗った船団が遅れているんだ\n本物のモリー・ジョーンズと、ちなみにとても美しいご主人様に会いたいなら、一ヶ月後にここへ来ることだ。 一日でも早く来ても無駄だぞ。";
			link.l1 = "どうやら、あなたの妹モリー・ジョーンズはフォックス嬢に仕えていて、現在は大西洋の向こう側に住んでいるのですね？ ";
			link.l1.go = "sister_2";
		break;
		
		case "sister_2":
			dialog.text = "まさにその通りだ！最後の使者からの報告によれば、護国卿クロムウェル閣下自らが派遣した海軍戦隊が、 わずか一ヶ月前にロンドンを出発する予定だったそうだ。キャサリンが乗ったブリッグ船「アルバトロス」 も同行するはずだった。次の郵便パケット船で、それが本当かどうかわかるだろう。まだ船は到着していないし、大佐は 「アルバトロス」が単独で航海するのを厳しく禁じていたのだ。\n彼の最愛の妻がフランスの私掠船の襲撃で亡くなったことを知っていたか？大佐にとっては辛い出来事で、 今も大海原の危険を恐れている……だから、モリー・ジョーンズの件では力になれないぞ、船長！植民地にはモリーという名の娘が山ほどいるしな！それに、 イギリスでジョーンズという姓は、姓がないのと同じくらいありふれている！\nアンティグアの海の男なら誰でも、俺と俺の指揮官のことは知っている。 困った目に遭った娘が俺に助けを求めてくるのも不思議じゃないさ。助けてやりたいが、身代金を払う金がない。 大佐は俺に三ヶ月分の給料をまだ払っていないし、俺の給料も他のみんなの分も、「アルバトロス」と一緒に届くんだ。";
			link.l1 = "どうやら私の勘違いだったようですね。ともかく、ご説明ありがとうございます。";
			link.l1.go = "sister_3";
		break;
		
		case "sister_3":
			dialog.text = "いえいえ、船長。";
			link.l1 = "...";
			link.l1.go = "sister_4";
		break;
		
		case "sister_4":
			DialogExit();
			AddQuestRecord("Terrapin", "3");
			pchar.questTemp.Terrapin.Catherina = "take"; // возможен вариант с Кати
			DeleteAttribute(pchar, "questTemp.Terrapin.Benjamin");
		break;
		
		// Робер Мартэн
		case "Rober":
			PlaySound("Voice\English\sharlie\Rober Marten-01.wav");
			dialog.text = "何の用だ！？話したくない。";
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "rober")
			{
				link.l1 = "用事があるんだ、船長。あんた、あまり元気がなさそうだな。俺の提案で少しは気分が晴れるかもしれねえぜ。";
				link.l1.go = "rober_1";
			}
			else
			{
				link.l1 = "静かにしろ、ラムでも飲め。俺のミスだ、すまねえ。";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Rober";
		break;
		
		case "rober_1":
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Terrapin_LateBaster.over = "yes"; //снять таймер
			dialog.text = "その響きはなかなか魅力的だな！それにお前の顔、どこかで見たことがある気がするんだが……どこで会ったか思い出せねえ。さあ、教えてくれよ！";
			link.l1 = "ティボーとの取引については知ってるぜ……安心しな、相棒！俺を怖がる必要はねえ。お前に提案したい取引があるんだ。";
			link.l1.go = "rober_2";
		break;
		
		case "rober_2":
			dialog.text = "畜生め！あの酔っ払い野郎が……！俺はうまくやれなかった……";
			link.l1 = "その通りだ。お前の水夫は口が軽かったが、奴の噂は俺以外には広まっちゃいねえ。しかも、 その噂もこれ以上広がることはねえさ。だって、お前がきっちり始末したんだろう？";
			link.l1.go = "rober_3";
		break;
		
		case "rober_3":
			dialog.text = "カランバ！今やっと思い出したぜ！お前はドイリー大佐をコテンパンにして、島ごと奪った男じゃねえか！ オランダ西インド会社の大きな取引にも関わってたし、西インドの貴族ともつるんでる……お前の名前は…… "+GetFullName(pchar)+"、だろう？";
			link.l1 = "なかなか正確な情報を持っているな。そう、俺だ。だが、ロベール、少し落ち着いてくれないか？";
			link.l1.go = "rober_4";
		break;
		
		case "rober_4":
			PlaySound("Voice\English\sharlie\Rober Marten-02.wav");
			dialog.text = "うおおっ！まあ、どうやって落ち着けってんだよ、諸島で一番有名な海の野郎が俺に目をつけただけじゃなく、 俺の商売まで嗅ぎつけやがったんだぞ！一体何を考えてあのブリッグを襲ったんだ、俺は！何が望みなんだよ、あんたは！ ？";
			link.l1 = "黙って俺の話を聞け。どうやら俺たち二人ともルヴァスールの首を皿に乗せてやりたいって思ってるようだな。 あの尊大な自慢屋は調子に乗りすぎて、ヤバい連中の怒りを買っちまった。俺はこの島の勢力図を塗り替えて、 ド・ポワンシーを思い知らせてやるつもりだが、同胞の血をこれ以上流したくはねえ。ましてや、 あんな汚い盗人のためにな。お前は俺を手伝える。そして俺も、お前とティボーが特権を守れるように力を貸せるぜ。";
			link.l1.go = "rober_5";
		break;
		
		case "rober_5":
			dialog.text = "待て、待て！俺の耳を疑うぜ！今日は運命の女神が俺に微笑んでるな。そうだ、お前の言う通り、俺たちの目的は同じだ。 お前と組めば、もっと面白くなりそうだ……ティボーは剣の腕はいいが、叔父の喉を掻き切る度胸はねえ……だが、お前みたいな狡猾な鮫ならやれるだろう。お前の名声はよく知れてるぜ\n保証なんていらねえが、代わりに女を渡してもらう。俺がカリブでの用事を片付けるまで、人質として必要なんだ。 すぐにイギリスのフリゲートが俺を追い回し始めるだろう。くそっ、あのブリッグを襲ったのは何の悪魔が憑いたんだ！ 隊から離れてて、あんなに楽な獲物に見えたのによ……";
			link.l1 = "彼女の何がそんなに特別だったんだ？ルヴァスールから隠していたあの娘のことか？";
			link.l1.go = "rober_6";
		break;
		
		case "rober_6":
			dialog.text = "ああ。ティボーにあの娘と手を切るよう説得しなければならん。私が彼に、あの娘が何者か調べている間、 面倒を見てくれと頼んだのだが、この“ミス・ジョーンズ”とかいう女にすっかり夢中になってしまって、今やアンリは私にまで彼女を隠している始末だ！ あの妖しい人魚を私のもとへ連れてこい。そうすれば町外れでルヴァスールと会う場を設けてやる。その時、 お前はやつを待ち伏せする機会を得られるだろう。私はフィッシュアイ・ビーチで待っている。";
			link.l1 = "取引成立だ。さて、ティボーをどうやって捕まえるか教えてくれ。";
			link.l1.go = "rober_7";
		break;
		
		case "rober_7":
			dialog.text = "酒場の連中に聞けば、彼の家まで案内してくれるだろう。アンリはなかなか目立つ男だ。暴露すると脅して、 女を俺のところに連れて来させろ。同じ日に、 ルヴァスールに甥が街の牢獄に珍しい美女を隠していることを知らせてやる\n私の使者が酒場でお前を見つけるだろう。アンリを見つけられなかった後、総督は少人数の部下を連れて牢獄に向かう。 そうすれば、お前は彼とゆっくり話す機会を得られるはずだ。";
			link.l1 = "「その娘はどこへ連れて行けばいい？」";
			link.l1.go = "rober_8";
		break;
		
		case "rober_8":
			dialog.text = "「自分で彼女を浜辺まで連れて来るように伝えろ。ついでに俺が少し話をしてやる……」";
			link.l1 = "よし、話はまとまったな。トルトゥーガで会おう！";
			link.l1.go = "rober_9";
		break;
		
		case "rober_9":
			dialog.text = "すべてが計画通りに進めば、もう二度と会うことはないだろう。\n少なくとも、私はそう願っている。\nさらばだ！";
			link.l1 = "...";
			link.l1.go = "rober_10";
		break;
		
		case "rober_10":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "Baster_tavern", "goto", "goto2");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina")) AddQuestRecord("Terrapin", "6");
			else AddQuestRecord("Terrapin", "5");
			pchar.questTemp.Terrapin = "tortuga";
			// создаем Тибо
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Tibo", "Tibo", "man", "man", 35, FRANCE, -1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_18", "pistol4", "bullet", 250);
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.name = "Henry";
			sld.lastname = "Thibaut";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "tibo";
			sld.greeting = "Tibo";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			TakeNItems(sld, "potion2", 8);
			TakeNItems(sld, "potion3", 5);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 40, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateTortuga", 0, 0, 20, false); // таймер
			SetFunctionLocationCondition("Tonzag_AtTortuga", "Tortuga_town", false);
		break;
		
		case "rober_abordage":
			dialog.text = "うおっ！まさかこんなことになるとは…お前は俺の魂を取りに来たんだろ？約束通りに全部やったじゃねえか！なんでだよ！？";
			link.l1 = "ロベール、お前には判決が下されている。その執行を任されたのが私だ。だから私は自分の任務を果たしているのさ。";
			link.l1.go = "rober_abordage_1";
		break;
		
		case "rober_abordage_1":
			dialog.text = "悪魔め！こんなのありえない！あいつがこんなに早く全部知るはずがない！それに、どうやって知ったんだ！？";
			link.l1 = "フォックスのことか？いや、違う。あいつが俺を寄越したんじゃねえ。大佐はまだお前が娘を斬ったことすら知らねえよ。 お前の昔の仲間、アンリ・ティボーが、お前を殺したがってるんだ。俺を雇ったのもあいつさ。";
			link.l1.go = "rober_abordage_2";
		break;
		
		case "rober_abordage_2":
			dialog.text = "あのくそったれの男娼め！「ヴォルティジュー」に乗ってた時にカニの餌にしてやりゃよかったぜ……あの野郎、お前にいくら約束しやがったんだ？";
			link.l1 = "自分の首にいくらの値がついてるか知る機会なんて、そうそうないだろう、ロベール？\nティボーはお前に二十五万と値をつけてたが、俺がもっと高く売り込んでやったんだ。\nお前の値段は三十万銀ペソだ、相棒。嬉しいだろう？";
			link.l1.go = "rober_abordage_3";
		break;
		
		case "rober_abordage_3":
			dialog.text = "ちょっと待ってくれ……取引しよう！もっと払うから！";
			link.l1 = "何の金でだ、ロベール？お前が嘘をついてるのは間違いない。お前にはアンリが約束したほどの金はないだろう。それに、 それが一番の問題じゃない。もし一つの事実がなければ、俺はアンリの提案――お前を追い詰めて、チボーとの汚い商売に終止符を打つという話――を断っていたさ。";
			link.l1.go = "rober_abordage_4";
		break;
		
		case "rober_abordage_4":
			dialog.text = "「それはどんな事実だ？」";
			link.l1 = "お前はキャサリン・フォックスを殺したな。あの可哀想な娘の罪は、フォックス大佐の娘として生まれただけだ。俺は、 お前みたいに無力な女を殺す卑怯者が大嫌いだ！取引なんて絶対にしない。考える価値もない。無駄口を叩くな。";
			link.l1.go = "rober_abordage_5";
		break;
		
		case "rober_abordage_5":
			PlaySound("Voice\English\sharlie\Rober Marten-03.wav");
			dialog.text = "くそっ！他にどうしろって言うんだ！？あいつを生かして、いつまでも船に隠しておくわけにはいかなかったんだ！\nそれにお前は誰だ……このろくでなし、野郎、殺し屋が、俺に道徳を説くつもりか！自分を見てみろよ！その“やり方”を！\nお前だって俺と大して変わらねえだろうが！";
			link.l1 = "もういい。マルタン、剣を抜け！決着をつける時だ。";
			link.l1.go = "rober_abordage_6";
		break;
		
		case "rober_abordage_6":
			dialog.text = "地獄で会おうぜ！";
			link.l1 = "...";
			link.l1.go = "rober_abordage_7";
		break;
		
		case "rober_abordage_7":
			DialogExit();
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// Тибо, вариант без Кати
		case "tibo":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "俺の家で何してるんだ、旦那？";
			link.l1 = TimeGreeting()+"、ティボー旦那。あなたのご存知の男、ロベール・マルテーヌ船長の代理で参りました。";
			link.l1.go = "tibo_1";
		break;
		
		case "tibo_1":
			dialog.text = "ふむ。それで？どうした？";
			link.l1 = "マルテン船長が今すぐフィッシュアイ・ビーチであなたとお会いしたいそうです。\nただし、お一人ではなく、モリー・ジョーンズもご一緒にお越しいただきたいとのこと。\n私の言いたいこと、わかりますね？";
			link.l1.go = "tibo_2";
		break;
		
		case "tibo_2":
			PlaySound("Voice\English\sharlie\Henry Thibault-01.wav");
			dialog.text = "あいにくですが、旦那、知りません。モリー・ジョーンズなんて聞いたこともありませんし、ロバートが私のもとへ、 見たこともない全権大使を送る理由もありません。ご参考までに申し上げますが、旦那、 私はこの島で総督である叔父に次ぐ二番目の男ですので……";
			link.l1 = "人生とは予測できぬ獣だな、アンリ……今はお前がこの島で二番目の男だが、数時間後には地下牢で鎖につながれているかもしれん……しかも、たった一ペソもくれやしない奴のためにだ。お前は叔父上の命令に背いたな、ティボー旦那？ お前にとって大事なのは、あの奔放な娘か、それとも自分の命か？";
			link.l1.go = "tibo_3";
		break;
		
		case "tibo_3":
			dialog.text = "なんだと…嘘ついてやがるな！でたらめ言ってんじゃねえよ！";
			link.l1 = "お前も他の誰と同じように、叔父の激しい気性をよく知っているはずだ。ルヴァスールは日が沈む前に、 お前があの娘を隠していることを必ず嗅ぎつけるだろう。ロベールがどうやってそれを知ったのかは聞くな、 俺の言葉を信じろ――あいつは死ぬほど怯えていて、今にも錨を上げて出航する気だ。町に入る勇気もなくて、 代わりにこの伝言を届けるために俺に大金を払ったんだ。";
			link.l1.go = "tibo_4";
		break;
		
		case "tibo_4":
			dialog.text = "くそっ……そんなはずがない！";
			link.l1 = "決めるのは旦那だ。マルテーヌはもう二時間以上は待たないぜ。自分の首が大事だからな。 まだトルトゥーガの岸に残ってるのも、オランダ人の連中とどこかに隠れていないのも、友誼の証ってわけさ。";
			link.l1.go = "tibo_5";
		break;
		
		case "tibo_5":
			dialog.text = "カランバ！どうしておじさんがそれを知ったんだ？";
			link.l1 = "舌だよ、ヘンリー。噂好きな連中の舌さ。俺でさえ、 お前とロバートが仲間が拿捕したイギリスのブリッグから降りてきた美女をさらったって知ってるぜ。 ルヴァスールには隠してたんだろ…ったく。\nこの話を知ってるのが俺だけだと本気で思ってるのか？";
			link.l1.go = "tibo_6";
		break;
		
		case "tibo_6":
			dialog.text = "どうやら本当のことを言っているようだな、旦那。マルテーヌに伝えてくれ…";
			link.l1 = "ヘンリー、お前は分かってないと思うぞ。マルテーヌはお前を待っちゃくれない。お前の唯一の望みは、 あの娘をここから連れ出すことだ――お前とロベールの首に縄がかかってる理由でもある。さっさとあの娘を隠してる場所に走って行って、 可愛い手を取ってヴォルティジュー号まで連れて来い。すぐに見つけて、もっと早く連れて来るんだ。お前の叔父上には、 俺からは一言も言わないからな。";
			link.l1.go = "tibo_7";
		break;
		
		case "tibo_7":
			dialog.text = "わかりました。それでは、そうしましょう。ご親切に感謝します、旦那！";
			link.l1 = "礼には及びません、旦那。私の仕事には報酬が出ますから……あなたが茹で上がる前に、この窮地から抜け出してほしいだけです。";
			link.l1.go = "tibo_8";
		break;
		
		case "tibo_8":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			pchar.quest.Terrapin_wait.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_wait.win_condition.l1.date.hour  = sti(GetTime()+3);
			pchar.quest.Terrapin_wait.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_wait.win_condition.l2 = "location";
			pchar.quest.Terrapin_wait.win_condition.l2.location = "Tortuga_tavern";
			pchar.quest.Terrapin_wait.function = "Terrapin_SetEnvoy";
			pchar.questTemp.Terrapin = "cave";
			AddQuestRecord("Terrapin", "8");
			SetFunctionTimerCondition("Terrapin_ReturnTibo", 0, 0, 10, false);
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 4, false);
			} 
			else SetFunctionTimerCondition("Terrapin_LateDungeon", 0, 0, 2, false);
		break;
		
		// вариант с Кати
		case "tibo_9":
			pchar.quest.Terrapin_LateTortuga.over = "yes"; //снять таймер
			PlaySound("Voice\English\sharlie\Henry Thibault-02.wav");
			dialog.text = "「ここで何をしているんだ、旦那？私はあなたを招待していないぞ。」";
			link.l1 = TimeGreeting()+"「ティボー旦那。あなたの知っている人物の代理で参りました。彼の名はロベール・マルテン船長です。」";
			link.l1.go = "tibo_10";
		break;
		
		case "tibo_10":
			dialog.text = "ふむ。それで？どうした？";
			link.l1 = "マルテン船長が今すぐフィッシュアイ・ビーチであなたとお会いしたいそうです。\nただし、あなただけではなく、モリー・ジョーンズも一緒に来てほしいとのこと。\n私の言いたいこと、わかりますよね？";
			link.l1.go = "tibo_11";
		break;
		
		case "tibo_11":
			dialog.text = "残念ですが、旦那、知りません。";
			link.l1 = "それを言うと思っていたよ。もちろん、君が以前コロネル・フォックスの娘と面識があったとは思えないが……コロネル・フォックスは知っているだろう、あの悪名高いシー・フォックス団の指揮官で、 カリブでイングランドの敵に恐れられている男さ。君とロバートが大騒ぎを起こしたせいで、 今まで無事だったのが奇跡だ！ 君がイギリスのブリッグ船から捕らえてルヴァスールに隠していたあのモリー・ジョーンズという娘、 あれがコロネル・フォックスの娘、キャサリン・フォックスなんだ！";
			link.l1.go = "tibo_12";
		break;
		
		case "tibo_12":
			dialog.text = "な、なんだって？";
			link.l1 = "ずいぶん顔色が悪いぞ、旦那。\nよく聞け、ヘンリー、そしてしっかり覚えておけ。お前と相棒のロバートは首までトラブルに浸かってるんだ。 いつカリブにクロムウェルの艦隊が到着してもおかしくねえ。奴らはお前たちを狙ってくる。旗艦一隻だけでも、 お前が自慢するラ・ロッシュ号も乗組員も、数時間で木っ端微塵にされちまうだろう。どう思う？ あのイギリスのブリッグ船への襲撃とフォックスの娘を捕らえたことは、それだけの価値があったか？";
			link.l1.go = "tibo_13";
		break;
		
		case "tibo_13":
			dialog.text = "";
			link.l1 = "だが、それだけじゃない。お前の企みは俺だけじゃなく、他の者にも知られているんだ。お前の大事な叔父上、総督殿も、 お前があの好色な爺さんの厳しい命令に逆らい、 きっと自分のものにしたかったであろう娘を隠していたことを知ることになるぞ。どう思う、ヘンリー？ 叔父上はお前に何をするだろうな？あの人の激しい気性は、誰よりもお前がよく知っているはずだろう…";
			link.l1.go = "tibo_14";
		break;
		
		case "tibo_14":
			dialog.text = "全部嘘だ！";
			link.l1 = "そうかい？親愛なるアンリ、友人のマルタンに聞いてみな。俺をここに寄越したのはあいつだ。 ルヴァスールは日が沈む前にお前があの娘を匿っていることを知るだろう。 ロベールがどうやってそれを知ったのかは聞かないでくれ、ただ俺の言葉を信じろ――奴は肝を潰して、今にも錨を上げて出航しそうな勢いだ。町に入ることすら怖がっていたから、 俺にこの伝言を託したってわけさ。";
			link.l1.go = "tibo_15";
		break;
		
		case "tibo_15":
			dialog.text = "";
			link.l1 = "マルテンはもう二時間以上は待ってくれないぞ。自分の首が大事だからな。お前との友情の証として、 まだトルトゥーガの岸にいるだけで、本当ならオランダ人のところにでも隠れているはずだ。だが、 あの哀れなロベールはモリー・ジョーンズの正体すら知らない。まったく、 お前たち二人は女性の服装や見た目についての驚くべき無知さで俺を呆れさせてくれるよ！ 貴婦人とその召使いの区別すらつかないとはな！";
			link.l1.go = "tibo_16";
		break;
		
		case "tibo_16":
			dialog.text = "何の用だ？";
			link.l1 = "やっと若造からまともな言葉が出たな！よし、ティボー。今すぐあの娘を隠してる場所へ行って、 白い手をやさしく取って、マルタンのヴォルティジューがいるフィッシュアイ・ビーチまで急いで連れて行け。 計画が変わったと伝えるんだ……";
			link.l1.go = "tibo_17";
		break;
		
		case "tibo_17":
			dialog.text = "";
			link.l1 = "マルテンは俺との約束を守らなきゃならねえ。あいつがあの娘を自分の船に乗せようなんて考えるんじゃねえぞ。 あの娘は浜辺で俺を待つんだ。ロベールにも伝えろ。もし約束を守らなかったり、カトリーヌを連れ去ったり、 あの可愛い頭の髪一本でも傷つけたら、俺は一生かけてあの娘を探し出す。そして見つけたら、フォックス大佐の元へ――生きたまま届けてやる。だがな、お前ら二人は……バラバラにして連れ帰ってやるぜ。ああ、ちなみにチボー、お前も例外じゃねえからな。";
			link.l1.go = "tibo_18";
		break;
		
		case "tibo_18":
			dialog.text = "";
			link.l1 = "俺が何者で、どんな力を持っているかはロベールに聞けばいい。あいつはよく知ってるさ。 お前たち二人が俺の言う通りにすれば、みんな得をするんだ。ロベールは海賊稼業を続けられるし、 お前は今の特権を守ったまま、あの年寄りの叔父貴がくたばった時に遺産を手に入れられる。俺も…損はしねえってわけだ。これで全部分かったか？";
			link.l1.go = "tibo_19";
		break;
		
		case "tibo_19":
			PlaySound("Voice\English\sharlie\Henry Thibault-03.wav");
			dialog.text = "お前の言いなりになるくらいなら、永遠の地獄の業火で焼かれる方がマシだ…… "+GetFullName(pchar)+"！最初からお前だと気づかなかったとはな！この人殺しめ！俺やロバートを生かして帰すつもりはねえんだろう！お前の“やり口”は有名なんだぜ！モリーも……それにキャサリンも、そんな汚ねえ野郎に渡すもんか！トルトゥーガから生きては出られねえぞ、このクソ野郎！";
			link.l1 = "...";
			link.l1.go = "tibo_20";
		break;
		
		case "tibo_20":
			dialog.text = "";
			link.l1 = "止まれ、腰抜け！";
			link.l1.go = "tibo_21"; // patch
		break;
		
		case "tibo_21":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload_window", "none", "", "", "Terrapin_LevasserRoomEnter", 5); // patch
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload_window");
			LAi_RemoveLoginTime(npchar);
		break;
		
		case "tibo_22":
			pchar.quest.Terrapin_TiboCallOver.over = "yes"; //снять прерывание
			pchar.quest.Terrapin_tibo_call.over = "yes"; //снять прерывание
			PlaySound("Voice\English\sharlie\Henry Thibault-04.wav");
			dialog.text = "やっと来たか！船長 "+GetFullName(pchar)+"、お越しいただき大変嬉しいです。どうぞ、中へお入りください。お掛けになりませんか。何かお飲み物はいかがですか？ 実は、あなたにとっても儲かる商談があるんですよ、友よ…";
			link.l1 = "ほう、今日はずいぶんご丁寧ですね、Thibaut様……座っている場合じゃありません。本題に入りましょう。";
			link.l1.go = "tibo_23";
		break;
		
		case "tibo_23":
			dialog.text = "その提案は、あなたもご存知のロベール・マルテン、かつてガレオン船『ヴォルティジュー』の船長だった、 私のかつての友人であり仲間に関するものです…";
			link.l1 = "それで、君とロベールはもう友達じゃないのか？面白い展開だな。";
			link.l1.go = "tibo_24";
		break;
		
		case "tibo_24":
			dialog.text = "船長、どうか私の助けを求める理由をお聞きください、そうすればすべてが明らかになります。ご存知の通り、 マルテーヌはイギリスのブリッグ船と戦い、捕虜としてイギリス人の女中モリー・ジョーンズを捕らえました――この騒動のすべての元凶です。";
			link.l1 = "もちろん、知っています。私の理解では、あなたは私の指示に従い、あの娘をマルテーヌの船に連れて行ったのでしょう？ ";
			link.l1.go = "tibo_25";
		break;
		
		case "tibo_25":
			dialog.text = "ああ、俺がやったんだ。でも毎日後悔してるよ。モリーは本当に魅力的で美しい娘なんだ、 あんな子に会ったのは初めてだった。正直に言うと、俺は彼女に恋をした。彼女も俺のことが好きだって、 自分で言ってくれたんだ！叔父貴に彼女を取らせるわけにはいかなかったんだ\n彼女を「ヴォルティジュール号」まで護送していたとき、誰も女の子を隠していないと分かれば、 あのスケベな年寄りも落ち着くだろうと思ってた。それからロベールが彼女をトルトゥーガに連れて帰り、 俺は安全に自分のところへ移せるはずだった。とにかく、それがマルテンと交わした約束だった。でも、 結果は違ったんだ\n叔父貴が殺されたと知ったとき、もうモリーを隠す理由はなくなったから、「ヴォルティジュール号」 がモリーを乗せて到着するのをじっと待っていたんだ。";
			link.l1 = "彼女は到着したか？";
			link.l1.go = "tibo_26";
		break;
		
		case "tibo_26":
			dialog.text = "ああ。残念ながら、モリーは船にいなかった。ロバートはまるでルシファー本人と鉢合わせしたかのように動揺していた。 短い遠征の間に、彼はどういうわけか恐ろしい事実を突き止めたんだ――あの娘、モリーはモリー・ジョーンズなんかじゃなくて、キャサリン・フォックスだった！シーフォックス隊、 イギリス海兵隊の精鋭部隊を率いるフォックス大佐の実の娘だ！その意味が分かるだろう！？";
			link.l1 = "畜生、なんてこった！こりゃ間違いなくロバートも恐れる理由があるってわけだな。\nだが、どうしてこんなことになっちまったんだ？";
			link.l1.go = "tibo_27";
		break;
		
		case "tibo_27":
			dialog.text = "キャサリンが捕らえられたとき、彼女は自分の正体を隠すために、 乗り込みの際に亡くなった召使いの少女モリー・ジョーンズを装っていたんだ。 マルタンに本当の身分がばれるのを恐れていたのさ。実際、彼女はうまくごまかした。\nだが最後の航海の途中で、ロバートがなぜか彼女の真実を知ってしまった。 彼は彼女の手紙や書類を見つけたと言っていた……";
			link.l1 = "「じゃあ、その娘は今どこにいるんだ？『ヴォルティジュー』号に乗らなかったなら。」";
			link.l1.go = "tibo_28";
		break;
		
		case "tibo_28":
			dialog.text = "彼女は死んだ。イギリスのブリッグを襲撃したことでフォックスからの差し迫った罰を恐れたマルタンは、 唯一残っていた証拠を水中に隠すことにしたんだ。彼女は「アルバトロス」襲撃の最後の目撃者だった。";
			link.l1 = "だったら、いっそ全員の船乗りを殺した方がマシだったんじゃねえか……フェルナン・リュックみたいにな。そうじゃなきゃ、いつかあいつらが酒場で酔っぱらって、 余計なことをベラベラしゃべっちまうぜ……";
			link.l1.go = "tibo_29";
		break;
		
		case "tibo_29":
			dialog.text = "奴は自分の乗組員全員が血で結ばれていると信じている。ある意味では正しいかもしれねえ。だが、 俺はフォックス大佐をよく知ってる！あの男は娘をさらった犯人を突き止めるまで、死ぬその日まで探し続けるだろうよ！ ";
			link.l1 = "それは疑っていない。特にフランスの海賊が彼の妻を殺した後ではな。今度は娘まで……ところで、旦那、本当にカトリーヌが死んだと絶対に確信しているのか？もしかすると、 ロベールがどこかに彼女を隠しているのかもしれんぞ。";
			link.l1.go = "tibo_30";
		break;
		
		case "tibo_30":
			dialog.text = "間違いない。俺は「ヴォルティジュール号」の水夫と話したんだ。奴の言葉を信じた。奴は自分の目で見たんだ――あの娘の喉を掻き切って、足に砲弾を縛りつけて海に放り込むところをな。";
			link.l1 = "なんてことだ、神よ！あの可哀想な女の人……俺に何の用だ、ヘンリー？";
			link.l1.go = "tibo_31";
		break;
		
		case "tibo_31":
			dialog.text = "あの日以来、夜は一睡もできなくなった。いつも目の前にモリーが現れる……いや、正しくはキャサリンだ。俺が彼女を死へと導いてしまったんだ。 "+GetFullName(pchar)+"！それだけは自分を許せないんだ。それに、フォックスに幻想なんて抱いちゃいない。あの男は油断なんてしないし、 眠りもしないだろう。遅かれ早かれ、マルテーヌの足取りを掴んで、誰かに白状させて、 娘を殺した奴が誰か突き止めたら、地獄が始まるさ。この一件に少しでも関わった奴は、みんなただじゃ済まないぞ。";
			link.l1 = "それは俺も含まれるぜ。";
			link.l1.go = "tibo_32";
		break;
		
		case "tibo_32":
			dialog.text = "ああ、俺も同じ気持ちだ。だからこそ、フォックスより先にマルタンを見つけてほしいんだ。あの野郎を探し出して殺せ。 できるなら、まず苦しませてやれ。哀れなカトリーヌのためにな。終わったら、 あいつが指にはめてる太い指輪ごと指を切り落として、それを証拠として俺のところに持ってこい\nあの曲がった指と指輪はよく知ってる。それをやってくれたら、銀貨二十五万を払おう。";
			link.l1 = "どうやら、亡くなったおじ上からかなりの遺産を受け取ったようだな、安らかに眠れってやつか？さて、ヘンリー、 どうしてこの件で俺に助けを求めようと思ったんだ？";
			link.l1.go = "tibo_33";
		break;
		
		case "tibo_33":
			dialog.text = "「私もあなたについていくつか知ったことがあるからです」 "+GetFullName(pchar)+"。簡単だったさ、お前は有名人だからな。ただし、本当は誰のために働いているのかは分からない。プアンシーなのか、 オランダ人なのか、イギリス人なのか、それともヤン・スヴェンソン男爵か……だが一つだけはっきりしている。お前は繊細で目立たない仕事を引き受け、きっちりやり遂げる。 そしてその報酬はたっぷりもらう。しかも何より、スペイン人とは無関係だ\n結局のところ、俺の伯父の遺産を俺が相続することになったあの事件にも、お前は関わっていたじゃないか。とぼけるな……二十五万というのは悪くない金だ。マルテンの居場所を教えてやる。あとは奴の船を捕まえて乗り込むだけだ。";
			link.l1 = "もう十万払ってくれりゃ、マルテンの始末は俺が引き受けてやるぜ。";
			link.l1.go = "tibo_34";
			link.l2 = "残念ですが、ティボー旦那、マルテンとフォックス大佐の件は私抜きでご自分で解決していただくしかありません。 私としては、娘さんの運命やその死に関わった者たちについて、大佐に一切知らせないことをお約束します。\nごきげんよう、旦那。";
			link.l2.go = "tibo_exit";
		break;
		
		case "tibo_exit":
			DialogExit();
			AddQuestRecord("Sharlie", "26");
			NextDiag.CurrentNode = "tibo_over";
		break;
		
		case "tibo_34":
			dialog.text = "旦那、お願いです…神に誓って、宝箱に何百万も隠しているわけじゃありません、本当です！ あなたの働きにお金がかかるのは分かっています、だからこそ最初に二十五万すぐにお渡ししたんです…分かりました…じゃあ、さらに五万金貨を上乗せします。それ以上は本当に無理です！";
			link.l1 = "よし、取引成立だ。マルテンを最後に見た場所はどこだ？";
			link.l1.go = "tibo_35";
		break;
		
		case "tibo_35":
			dialog.text = "彼はカラカスのスペイン領本土へ南下し、ドン・ディエゴ・フランシスコ・デ・ケレス総督との謁見に成功したらしい。 どうやら何らかの賄賂を渡したようで、ドン・ディエゴはロベールにスペイン王冠の庇護を与えた。ロベールは 「ヴォルティジュー」を売却し、今では大型ガレオン船「インファンタ」の船長になっている。総督に賄賂を渡し、 あのような大型軍艦を購入・装備できるとは、相当な蓄えがあったに違いない\n次は新しい船でカラカスからサント・ドミンゴへ、スペイン艦隊の一員として航海する予定だ。 私の手先が掴んだ情報はそれだけだ。マルタンを捕まえる唯一の機会は、そのスペイン艦隊に追いつくことだ\nもし奴らがサント・ドミンゴに到着すれば、全て終わりだ。ロベールが次にどこへ向かうかは全く分からない。 まるでウサギが巣穴に潜るように姿を消し、二度と見つけられなくなるだろう。";
			link.l1 = "了解だ。奴らを迎え撃つぜ。";
			link.l1.go = "tibo_36";
		break;
		
		case "tibo_36":
			dialog.text = "それと、指輪をはめた指も忘れるなよ！それが俺たちの取り決めの絶対条件だぜ！ロベールが確実に死んだと、 俺は絶対に確信したいんだ！";
			link.l1 = "よし。時間を無駄にせず、すぐに出航するぞ！";
			link.l1.go = "tibo_37";
		break;
		
		case "tibo_37":
			DialogExit();
			AddQuestRecord("Sharlie", "27");
			Terrapin_CreateRoberConvoy();
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			NextDiag.CurrentNode = "tibo_time";
		break;
		
		case "tibo_time":
			dialog.text = "「マルテンはまだカリブでその臭い存在を撒き散らしてやがるのか、船長？」";
			link.l1 = "奴はもう長くはもたねえ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_time";
		break;
		
		case "tibo_38":
			dialog.text = "「マルテンがカリブに現れて臭いを撒き散らしてやがるのか、船長？」";
			link.l1 = "もう心配はいらない。フォックス大佐を恐れる必要はもうないし、あなたのカトリーヌの仇も討った。これがその証拠だ。 ";
			link.l1.go = "tibo_39";
		break;
		
		case "tibo_39":
			RemoveItems(pchar, "finger", 1);
			dialog.text = "ああ……間違いなくマルテンの指だ。感心させられてばかりだぜ、船長 "+GetFullName(pchar)+"！まさにあなたが得た評判にふさわしい人物ですね。";
			link.l1 = "支払いの話に移ろうか、ティボー？";
			link.l1.go = "tibo_40";
		break;
		
		case "tibo_40":
			AddMoneyToCharacter(pchar, 250000);
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You've received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "すべて準備できた。ほら、報酬を受け取れ。";
			link.l1 = "感謝する。事前にそれを用意できて嬉しいよ。さて、ヘンリー、今後はこんな面倒ごとに巻き込まれず、 もっと良い友人を選ぶことを願っている。幸運を祈る！";
			link.l1.go = "tibo_41";
		break;
		
		case "tibo_41":
			dialog.text = "助けてくれてありがとうございます、船長！友人みんなにあなたを推薦します。ご武運を！";
			link.l1 = "...";
			link.l1.go = "tibo_42";
		break;
		
		case "tibo_42":
			DialogExit();
			AddQuestRecord("Sharlie", "31");
			NextDiag.CurrentNode = "tibo_stop";
		break;
		
		case "tibo_stop":
			dialog.text = "はい、旦那 "+GetFullName(pchar)+"？私に用でもあるのか？";
			link.l1 = "いいえ、Thibaut様。ちょっと立ち寄っただけです。さようなら！";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_stop";
		break;
		
		case "tibo_late":
			dialog.text = "「あっ、」 "+GetFullName(pchar)+"…おい、何をぐずぐずしてやがる！で、ロベール・マルテンがどこにいるか、誰か知ってる奴はいねえのか！？ フォックス大佐が全部嗅ぎつけたら、俺はとんでもねえことになるぞ…";
			link.l1 = "なるほど。遅すぎたようですね。申し訳ありません、ティボー旦那、しかし非常に差し迫った用事で遅れてしまいました。 あなたの時間を無駄にはしません。さようなら。";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		case "tibo_over":
			dialog.text = "何の用だ、 "+GetFullName(pchar)+"？雑談してる暇はない。もっと重要な用事があるんだ。フォックスより先にマルテンを見つけなきゃ……";
			link.l1 = "はいはい。今行くよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "tibo_over";
		break;
		
		// посланник от Мартэна
		case "envoy":
			dialog.text = "お前が船長か "+GetFullName(pchar)+"?";
			link.l1 = "よく来たな、相棒。話を聞こうじゃねえか。";
			link.l1.go = "envoy_1";
		break;
		
		case "envoy_1":
			dialog.text = "「あなたの債務者が、『仕事は済んだ、魚は一時間もしないうちに網にかかる』と伝えてほしいそうだ。 だから急いだほうがいいぞ。」";
			link.l1 = "承知しました。ありがとうございます！";
			link.l1.go = "envoy_2";
		break;
		
		case "envoy_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Terrapin", "9");
			pchar.quest.Terrapin_cave.win_condition.l1 = "Timer";
			pchar.quest.Terrapin_cave.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.Terrapin_cave.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.Terrapin_cave.win_condition.l2 = "location";
			pchar.quest.Terrapin_cave.win_condition.l2.location = "Tortuga_cave";
			pchar.quest.Terrapin_cave.function = "Terrapin_LevasserInCave";
		break;
		
		// Левассер в пещере
		case "levasser_cave":
			pchar.quest.Terrapin_LateDungeon.over = "yes"; //снять таймер
			dialog.text = "なんでこんなところをうろついてやがるんだ？お前は誰だ？さっさと答えろ！";
			link.l1 = "てめえは何者だ、そしてなんでそんなくだらねえ質問を俺にするんだ？";
			link.l1.go = "levasser_cave_1";
		break;
		
		case "levasser_cave_1":
			dialog.text = "「何だと！？この鼻たれ小僧め！俺が誰かって？俺はこの島の総督、フランソワ・ルヴァスール、 セニョール・ド・ルネ・ド・ボワドゥフレ・ド・レットルだ！この島のすべては俺の管轄下にあるんだ！ お前もこの俺の縄張りにいる間は例外じゃねえぞ、小僧！」\n";
			link.l1 = "ほうほう……ご本人登場ってわけか？迷子になったな、ルヴァスール、レネ・ド・なんとかの旦那よ。お前の時間は終わりだ。 総督フランソワ・ロンヴィリエ・ド・プアンシーの命令により、お前はその地位を剥奪され、即刻死刑を宣告された！ 俺が裁判官であり、処刑人だ！最後に言い残すことはあるか？";
			link.l1.go = "levasser_cave_2";
		break;
		
		case "levasser_cave_2":
			dialog.text = "";
			link.l1 = "どうせ諦める気はねえんだろうし、俺に情けを乞うても無駄だぜ。さあ、剣を抜け！";
			link.l1.go = "levasser_cave_3";
		break;
		
		case "levasser_cave_3":
			dialog.text = "くそっ！あれはプアンシーの手先だ！剣を抜け！奴を殺せ！";
			link.l1 = "踊りましょう。";
			link.l1.go = "levasser_cave_4";
		break;
		
		case "levasser_cave_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_cave")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=2; i<=4; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			// подкрепление
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+7;
			int iScl = 30 + 2*sti(pchar.rank);
			for (i=5; i<=9; i++)
			{		
				sld = GetCharacter(NPC_GenerateCharacter("TerrapinGuard"+i, "citiz_5"+i, "man", "man", iRank, PIRATE, -1, true, "quest"));
				FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_19", "pistol5", "bullet", iScl*2+50);
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "goto"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserCaveDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// Левассер в комнате таверны
		case "levasser_room":
			dialog.text = "ここで一体何してやがる！？お前は誰だ？今すぐ答えろ！";
			link.l1 = "どうだ！これは予想外だったな……ルヴァスール旦那ご本人で間違いないか？";
			link.l1.go = "levasser_room_1";
		break;
		
		case "levasser_room_1":
			dialog.text = "そうだ、俺がこの島の総督、フランソワ・ルヴァスール、ルネ・ド・ボワドゥフレ・ド・レットル領主だ！\nこの島にあるものすべては俺の管轄下にある！\nお前も俺の縄張りを歩いている以上、その例外じゃねえ、ろくでなしめ！\n質問に答えろ！\n軍曹、この扉を閉めろ。この男、何か企んでやがるぞ！";
			link.l1 = "あなたは本当に鋭いですね、ルヴァスール旦那、ルネ・ド・なんとかの領主殿。\n私がここにいることは、あなたにとって嬉しい知らせではないでしょう。\n総督フランソワ・ロンヴィリエ・ド・プアンシーの命により、あなたはその職を解かれ、即刻死刑を宣告された！\n私はあなたの裁判官であり、処刑人でもある！";
			link.l1.go = "levasser_room_2";
		break;
		
		case "levasser_room_2":
			dialog.text = "";
			link.l1 = "どうせ諦める気はないんだろうし、俺に情けを乞うても無駄だぜ。さあ、剣を抜け！お前は俺の仕事だ、 個人的な恨みはねえ。ただ王冠に仕えてるだけさ、はは！軍曹、 俺が総督の命令を遂行してる間は手出ししない方がいいぞ！\n";
			link.l1.go = "levasser_room_3";
		break;
		
		case "levasser_room_3":
			dialog.text = "聞くな、軍曹！あいつはスペインの間者だ！殺せ！衛兵、助けてくれ！ここにスペイン野郎がいるぞ！";
			link.l1 = "実はスペインには行ったことがなくて、ナルボンヌだけなんだ。";
			link.l1.go = "levasser_room_4";
		break;
		
		case "levasser_room_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("TerrapinGuard"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Terrapin_LevasserRoomDied");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		// девушка на балконе
		case "roof_girl":
			dialog.text = "痛い！助けてくれ！兵隊！";
			link.l1 = "静かにしろ、この馬鹿め！お前が叫ばなきゃ、俺は何もしねえよ！";
			link.l1.go = "roof_girl_1";
		break;
		
		case "roof_girl_1":
			dialog.text = "殺さないでくれ！";
			link.l1 = "馬鹿なことを言うな！つい十分前に男がここを走り抜けたんだ。身なりのいい貴族だ。どこに隠れている？ 見ていないなんて言い訳はするなよ！";
			link.l1.go = "roof_girl_2";
		break;
		
		case "roof_girl_2":
			dialog.text = "ティボー様？";
			link.l1 = "なるほど、あいつのことを知ってるんだな！どこへ逃げやがった？答える気はあるのか、 それとも頭をガツンと揺すってやろうか？";
			link.l1.go = "roof_girl_3";
		break;
		
		case "roof_girl_3":
			dialog.text = "ああ、お願いです、私を傷つけないでください！ティボー旦那は逃げました、あっちの海の方へ。それで、 巻き上げ機から飛び降りて、水の中に落ちました。あんなに高い所からですから、きっと死んでしまったのでしょう…";
			link.l1 = "そうは思わないな。あいつは自殺なんてするような奴じゃねえ。中に入ったほうがいいぜ。今夜はここにいるのは危険だ。 ";
			link.l1.go = "roof_girl_4";
		break;
		
		case "roof_girl_4":
			dialog.text = "痛い！痛い！撃たないでくれ！";
			link.l1 = "何だって！？";
			link.l1.go = "roof_girl_5";
		break;
		
		case "roof_girl_5":
			DialogExit();
			LAi_SetActorType(pchar);
			PlaySound("People Fight\MushketShot.wav");
			DoQuestCheckDelay("Terrapin_GirlShot", 1.0);
		break;
		
		// Кати
		case "kathy":
			PlaySound("Voice\English\Armo02.wav");
			dialog.text = "お前は誰だ？俺を殺しに来たのか、それとも……もっとひどいことをしに来たのか？";
			link.l1 = "そんなことはありません、奥様。私はあなた、キャサリン・フォックスをセントジョンズのご父君のもとへお連れします。 その後、命令に背いたことでお父上に叱られるなら、私の罪もまた繰り返されることになりますね。ですが、 あれこれ心配をかけたにもかかわらず、娘が無事であることを大佐殿が喜んでくださることを願っています。";
			link.l1.go = "kathy_1";
		break;
		
		case "kathy_1":
			dialog.text = "神に感謝を！これは夢に違いない！私が誰だか知らないのか？君はフランス人でカトリックなのに、 わざわざここまで来て同胞の手から私を救おうとしたのか？命を賭けてまでフォックス大佐の娘のために？";
			link.l1 = "私がトルトゥーガに来た本来の理由はまったく別だったんだ。\nだが、美しいご婦人を盗賊どもの手に任せて立ち去るわけにもいかなかったのさ。";
			link.l1.go = "kathy_2";
		break;
		
		case "kathy_2":
			dialog.text = "あなたは高貴な紳士ですね！お名前は何とおっしゃいますか、旦那？";
			link.l1 = ""+GetFullName(pchar)+"。船長 "+GetFullName(pchar)+".";
			link.l1.go = "kathy_3";
		break;
		
		case "kathy_3":
			dialog.text = "教えてください、船長、本当に私をセントジョンズの父のもとへ連れて行ってくださるのですか？";
			link.l1 = "ああ、ただし奴はフランス人にはあまり好意的じゃないぜ。まあ、 イギリス人にもろくでなしはいるってことを思い出させてやるさ、しかもイギリスの士官にもな！ 俺はそのうちの一人を実際に見たことがある……リチャード・フリートウッドって名前だった。";
			link.l1.go = "kathy_4";
		break;
		
		case "kathy_4":
			dialog.text = "もしアンティグアまでたどり着けたら、フランス人の中にも本物の騎士がいると父上に全力で説得してみせます。";
			link.l1 = "それは大変ありがたいです……さて、私の守護天使たちが街の屋根の上で私の道を見守り、すでに我々の帰還を待っていてくれることを願います。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_OwrInGrot");
		break;
		
		case "kathy_5":
			PlaySound("Voice\English\Armo01.wav");
			dialog.text = "今まであなたが約束を守ってくれるなんて信じられませんでした！最近、 私には恐ろしいことや卑劣なことばかりが起きていたのです……船長、あなたのおかげで人と騎士道への信頼を取り戻せました、感謝します。お時間がある時に、 ぜひ私の父に会いに来てください！\n父はあなたのような男を尊敬しています。それに、あなたがフランス人であることも関係ありません。 私は父があなたの国に対する考えを改めるよう、できる限り説得してみせます。";
			link.l1 = "ありがとう、Catherine。せっかくのご親切な申し出、いずれ利用させていただくかもしれません。";
			link.l1.go = "kathy_6";
		break;
		
		case "kathy_6":
			dialog.text = "ぜひそうしていただきたいです、船長。私のためにしてくださったこと、本当に感謝しています。決して忘れません。";
			link.l1 = "さあ、急いでお父様のところへ行きなさい。きっとお会いできて喜ばれるでしょう。もしかしたら、 もう畑から戻っていらっしゃるかもしれませんね。\nさて、私はそろそろ失礼します。さようなら！";
			link.l1.go = "kathy_7";
		break;
		
		case "kathy_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.lifeday = 0;
			SetFunctionTimerCondition("Terrapin_ReturnFox", 0, 0, 3, false); // Фокса на место
			pchar.questTemp.Terrapin_KathyReward = "true"; // награда за спасение Кати 160912
		break;
		
		// наш матрос
		case "terrapin_grot":
			dialog.text = "やっと戻ったな、船長！お前のことが心配でたまらなかったぜ！あの瓦屋根の上を駆け抜けて、 あんな恐ろしい高さから飛び降りるなんて、見事だったぜ！神に誓って、本当に無事じゃないかとヒヤヒヤしたんだ……\nおかえり、船長。ロングボートの準備はできてるぜ！";
			link.l1 = "素晴らしい。キャサリン、俺について来い！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Terrapin_GotoShip");
		break;
		
		case "tibo_sailor":
			dialog.text = "こんにちは、旦那。あなたが船長ですか "+GetFullName(pchar)+"?";
			link.l1 = "ああ、俺だ。どうしたんだ？";
			link.l1.go = "tibo_sailor_1";
		break;
		
		case "tibo_sailor_1":
			dialog.text = "ふう、やっと追いついたよ……君が知っているヘンリー・ティボーという紳士の代理で来たんだ。";
			link.l1 = "ヘンリー？それで、何の用だ？亡くなった親愛なる叔父の死で、 思いがけず遺産が転がり込んできた喜びでも分かち合いたいのか？";
			link.l1.go = "tibo_sailor_2";
		break;
		
		case "tibo_sailor_2":
			dialog.text = "ティボー旦那が至急トルトゥーガの邸宅までお越しいただきたいと申しております。高額な報酬の仕事があるそうです。 また、「ロベール・マルテン」という名前をあなたに伝えるようにとも言われました。興味が湧くはずですよ。";
			link.l1 = "そうか？それでヘンリーはどうしてそんな考えに至ったんだ？";
			link.l1.go = "tibo_sailor_3";
		break;
		
		case "tibo_sailor_3":
			dialog.text = "それから、もしこれでも彼に会いに行く気にならなかったら、さらにこう付け加えてほしいと頼まれたんだ――「ロベール・マルテーヌは死なねばならぬ」と。";
			link.l1 = "わかった、わかった……これは面白くなってきたな。二人の親友が今まさに口論したってわけか……君の言う通り、機会があればヘンリーに会いに行ってみるよ。";
			link.l1.go = "tibo_sailor_4";
		break;
		
		case "tibo_sailor_4":
			dialog.text = "ティボー様は、訪問を遅らせないようにとおっしゃっていました。「魚は十日で網から逃げてしまう」と、 まさにその言葉でした……";
			link.l1 = "彼とロバートは同じ話し方をするな。よし、ヘンリーに会いに行こう。";
			link.l1.go = "tibo_sailor_5";
		break;
		
		case "tibo_sailor_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("Terrapin_TiboCallOver", 0, 0, 10, false);
			AddQuestRecord("Sharlie", "25");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
