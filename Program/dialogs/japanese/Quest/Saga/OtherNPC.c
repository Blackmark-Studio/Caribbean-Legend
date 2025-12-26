// диалог прочих НПС по квесту Саги
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
			dialog.text = "何か用か？";
			link.l1 = "いいえ、何もありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
//---------------------------------------------Джимми в доме в Марун-Тауне------------------------------------
		case "Jimmy":
			dialog.text = "何の用だ？私が喪に服しているのが見えないのか！階段から蹴り落とされる前に消え失せろ！";
			link.l1 = "じゃあ、そのために階段付きのもっと大きな家でも買えばいいさ。そしたら階段から人を蹴り落とす話でもしようぜ、 英雄さんよ…";
			link.l1.go = "Jimmy_1_1";
			link.l2 = "どうしたんだ、ジミー、そんなに気を落として？美人が絡んでなきゃ、俺がこの先一生ラムを断つってもいいぜ！ お前みたいな海の狼が古い仲間に牙をむくなんて、女以外にありえねえだろ…";
			link.l2.go = "Jimmy_1_2";
		break;
		
		case "Jimmy_1_1":
			dialog.text = "俺はお前みたいな細かい奴が大嫌いだぜ！いつも一番いいところを持っていきやがる。 成り上がり者を一人も殺させてもらえなかったから、その鬱憤をお前で晴らしてやる！";
			link.l1 = "...";
			link.l1.go = "Jimmy_fight";
		break;
		
		case "Jimmy_fight":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_fight");
		break;
		
		case "Jimmy_1_2":
			dialog.text = "あぁ！？俺はお前を知ってるのか？全然覚えてねえぞ、くそっ…";
			link.l1 = "「私だ」 "+pchar.name+"！お前があの生意気なコートの野郎をもう少しで腸までぶちまけそうになった後、 ブルーヴェルドでは最高に楽しかったぜ。あいつの名前は何だったっけ？もう忘れちまったな……まあいい、もし海でまた会っても、あいつのコルベットの大砲なんざ気にしねえよ！";
			link.l1.go = "Jimmy_2";
		break;
		
		case "Jimmy_2":
			dialog.text = "奴の名前はアーサーだった！アーサー・ドノヴァン、「アービュタス」コルベットの船長だ！汚ねえ野郎め！ 俺があいつを地獄送りにしかけたって、あんたも認めるんだな？";
			link.l1 = "もちろんだ！あいつには全く勝ち目がなかったが、お前の仲間たちが邪魔しやがったんだ。許してやってくれ、 あいつらはお前が海軍士官殺しで絞首刑になるのを望んでなかったんだよ。";
			link.l1.go = "Jimmy_3";
		break;
		
		case "Jimmy_3":
			dialog.text = "くそっ！俺に船さえあればな！あの野郎はアンティグアの近くで簡単に追跡できるんだ……ははっ！もし奴を海の底に沈めてくれたら、借りができるぜ！";
			link.l1 = "取引成立だ、ははは！ところで、ルンバって本当にそこまで苦労する価値があるのか？";
			link.l1.go = "Jimmy_4";
		break;
		
		case "Jimmy_4":
			dialog.text = "もちろんだ！あんなに素晴らしい女は他にいないぜ。でも、あいつは俺のことを笑うだけさ。 みんなあの人魚を欲しがってる。水夫の何人かがこっそり教えてくれたんだが、 うちのジェイコブも俺のルンバそっくりの娘を探してるらしい。あいつも狙ってるんだよ！ これでどうやってあいつの命令に従えってんだ？";
			link.l1 = "静かにしろよ、相棒！壁に耳ありだ……それに、なんでジャックマンがルンバを探してると思う？";
			link.l1.go = "Jimmy_5";
		break;
		
		case "Jimmy_5":
			dialog.text = "ああ、間違いないぜ！あいつはヘンリー・ザ・ハングマンとか、金髪碧眼の二十歳くらいの娘を探してるらしい。 ベリーズのグラディス・チャンドラーって女がその娘の世話役だそうだ。";
			link.l1 = "待て！グラディスは苗字が違うんだ。それに、彼女は母親だぞ！";
			link.l1.go = "Jimmy_6";
		break;
		
		case "Jimmy_6":
			dialog.text = "ジャックマンは抜け目ない奴だ！油断してるところなんて絶対に捕まえられねえ！俺はしばらくルンバに言い寄ってて、 グラディスがちょうど二十年前にショーン・マッカーサーと結婚したって知ったんだ。それより前はベリーズに住んでた。 最初の旦那はピート・チャンドラーって名前だった。\n可哀想なピートは酔っ払い同士の喧嘩で殺されたらしい。マッカーサー自身が手を下したって噂もあるぜ、 当時からふっくらしたグラディスに気があったらしいからな。グラディスは赤ん坊を抱えた未亡人になった。 でもその子も父親の後を追うように、すぐ熱病で死んじまった。\nそれからほんの数ヶ月後、グラディスとショーンがブルーヴェルドに現れて、女の子を連れてきたんだ。 その子はマッカーサーの娘だって言ってた。でもよ、そんな短期間でグラディスがまた子供を産めるか？分かるか？";
			link.l1 = "このことを他の誰かに話したか？";
			link.l1.go = "Jimmy_7";
		break;
		
		case "Jimmy_7":
			dialog.text = "まだだ。黙ってろ、さもないと……まあ、俺のことは知ってるだろう！";
			link.l1 = "ああ、そうだよ。お前の口は腐ってやがる、誰にでも秘密をペラペラしゃべるからな。ルンバが追い出したのも当然だぜ、 このおしゃべり野郎め…";
			link.l1.go = "Jimmy_8_1";
			link.l2 = "もちろん！口は堅くするよ！さて、もう行かなくちゃ。じゃあな、ジミー。";
			link.l2.go = "Jimmy_8_2";
		break;
		
		case "Jimmy_8_1":
			dialog.text = "な、なんだと！？";
			link.l1 = "他の誰にも話せなくなるぞ……";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_KillToJimmy_kino");
		break;
		
		case "Jimmy_8_2":
			DialogExit();
			AddDialogExitQuestFunction("Saga_Jimmy_DlgExit");
		break;
// <-- Джимми 
		
//-------------------------------------------корвет Донована, абордаж-----------------------------------------
		//Донован
		case "Donovan_abordage":
			PlaySound("Voice\English\saga\Artur Donovan.wav");
			dialog.text = "うおお、てめえは化け物か！";
			link.l1 = "独り言かい、旦那！？ルンバはどこだ？";
			link.l1.go = "Donovan_abordage_1";
		break;
		
		case "Donovan_abordage_1":
			dialog.text = "何がルンバだ？俺の船にあだ名付きのクズなんざいねえ。ここはイギリス海軍の艦だぞ！";
			link.l1 = "とぼけるんじゃねえぞ、ドノヴァン。俺が誰のことを言ってるか、てめえには分かってるはずだ。\nあの娘はどこだ？ヘレンはどこにいる？答えろ、この汚ねえ野郎……";
			link.l1.go = "Donovan_abordage_2";
		break;
		
		case "Donovan_abordage_2":
			dialog.text = "ヘレンだと？俺の船に陸の売女なんざ乗せねえぞ、このクソ野郎！";
			link.l1 = "陸の売女はいないって？信じられねえな、だって今まさに目の前に一人立ってるじゃねえか……もう話す価値もねえな。死ね、この哀れな虫けらが！";
			link.l1.go = "Donovan_abordage_3";
		break;
		
		case "Donovan_abordage_3":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "Saga_AfterDonovanBoarding");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Takehelen = "true";//признак, что абордировали судно
		break;
		
		//наш матрос
		case "Tempsailor":
			dialog.text = "船長、ご指示通り全ての船室と貨物倉を捜索しました。貨物倉で鎖につながれた少女を発見しました…";
			link.l1 = "なんて野郎だ！やっぱりな……あの娘の鎖は外したか？";
			link.l1.go = "Tempsailor_1";
		break;
		
		case "Tempsailor_1":
			dialog.text = "かしこまりました、船長。彼女は無事にあなたの船に乗せられました。";
			link.l1 = "よくやった！あの娘を俺の船室へ連れて行け。ここが片付いたら話をしたい。";
			link.l1.go = "Tempsailor_2";
		break;
		
		case "Tempsailor_2":
			dialog.text = "「了解だぜ、船長！」";
			link.l1 = "...";
			link.l1.go = "Tempsailor_3";
		break;
		
		case "Tempsailor_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		break;
		//<-- абордаж корвета Донована
		
//----------------------------------------поиск Энрике Гонсалеса, Картахена----------------------------------
		//фальшивый Гонсалес №1, дом
		case "GonsalesA":
			dialog.text = "何か用か？";
			link.l1 = "やあ、絞首人！ブッチャー船長からよろしくとのことだ。";
			link.l1.go = "GonsalesA_1_1";
			link.l2 = "私の名はシャルル・ド・モール。私はセニョーラ・ゴンザレスの息子エンリケを、 彼女の古い友人の代理として探している。あなたがそのエンリケだと思うが…";
			link.l2.go = "GonsalesA_2_1";
		break;
		
		case "GonsalesA_1_1":
			dialog.text = "なんだと！俺はブッチャーなんて知らねえぞ！";
			link.l1 = "さあ、ヘンリー。なぜジャックマンの海賊たちがお前を狙っているのか教えろ。そうすれば傷つけたりしないぞ。";
			link.l1.go = "GonsalesA_1_2";
		break;
		
		case "GonsalesA_1_2":
			dialog.text = "助けて！海賊だ！殺される！";
			link.l1 = "黙れ、この馬鹿野郎！お前の叫び声で町中の半分がここに駆けつけちまうぞ。ああ、それが狙いか！？";
			link.l1.go = "GonsalesA_1_fight";
		break;
		
		case "GonsalesA_1_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesA");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesA_2_1":
			dialog.text = "ふむ……旦那、何かお間違いではありませんか。私は異国の家で育ちましたし、生みの母のことは覚えていません。 養育者の姓を名乗っています。母の名前は知りませんが、ゴンザレスだったとは思えません。 私について調べてくだされば、古くからの住人なら皆、私の言うことを証明してくれるはずです。 継父は有名な人物でしたし、実子がいなかったので、この家を私が継いだのです、そして……\n";
			link.l1 = "申し訳ありません。私の勘違いだったようです。さようなら。";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesA_3_1";
			else link.l1.go = "GonsalesA_2_2";
		break;
		
		case "GonsalesA_2_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "17");
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesA_3_1":
			dialog.text = "そうは思わない。";
			link.l1 = "「何だって？」";
			link.l1.go = "GonsalesA_3_2";
		break;
		
		case "GonsalesA_3_2":
			dialog.text = "ご存知かもしれませんが、最近我々の植民地が海賊どもに容赦なく襲撃されました。\nこの件については耳にしているでしょう？その襲撃のせいで、数えきれないほどの人々が苦しみました。 私は無事でしたが、先祖代々の商売が今や苦境に立たされています。\nそして、この災難の元凶は、海賊たちの頭目であるチャーリー・プリンスという悪党なのです。";
			link.l1 = "申し訳ありませんが、それが私に何の関係があるのですか？";
			link.l1.go = "GonsalesA_3_3";
		break;
		
		case "GonsalesA_3_3":
			dialog.text = "ははは、この無垢な子羊を見てみろよ！俺の損失はお前のせいなんだから、埋め合わせてもらおうじゃねえか。まあ、 一万五千ペソで手を打ってやるよ。それでお前が俺の家に来たことはなかったことにしてやるさ。";
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = "なんて執念深い連中だ……ほら、金だ。いいか、俺がこの町にいたことが誰かにバレたら、お前たちのところに戻ってくるからな。";
				link.l1.go = "GonsalesA_3_4";
			}
			link.l2 = "一万五千か？ふむ……お前の命がそんなに価値があるとは思えねえな。つまり、口封じに斬り捨てた方が安上がりってわけだ。";
			link.l2.go = "GonsalesA_3_5";
		break;
		
		case "GonsalesA_3_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			AddQuestRecord("Saga", "171");
		break;
		
		case "GonsalesA_3_5":
			dialog.text = "衛兵！海賊！殺人だ！";
			link.l1 = "黙れ、このバカ！";
			link.l1.go = "GonsalesA_3_6";
		break;
		
		case "GonsalesA_3_6":
			DialogExit();
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2;
			for (i=1; i<=2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SpSold"+i, "sold_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "soldier"));
				SetFantomParamFromRank(sld, iTemp, true);         
				LAi_SetWarriorType(sld); 
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("SpOfficer", "off_" + NationShortName(SPAIN) + "_" + (rand(1) + 1), "man", "man", iTemp, SPAIN, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 25, 100, 100, "blade_13", "pistol6", "bullet", 150);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesAK");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		// <-- участвовал в событиях Картахены
		
		// фальшивый Гонсалес №2, улицы
		case "GonsalesB":
			PlaySound("Voice\English\citizen\Pirati v Gorode-08.wav");
			dialog.text = "俺のカットラスが気に入ったみたいだな。欲しけりゃ売ってやってもいいぜ。大した金は取らねえよ、 ラムが飲みたくてたまらねえし、懐も空っぽなんだ。";
			link.l1 = "「それが一体俺に何の役に立つってんだ？森の悪魔があんたによろしくってさ。」";
			link.l1.go = "GonsalesB_1_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = "そうだな。確かに立派なカトラスだぜ。いくらだ？";
				link.l2.go = "GonsalesB_2_1";
			}
		break;
		
		case "GonsalesB_1_1":
			dialog.text = "「それよりも俺に百ペソか二百ペソでもくれた方がよっぽどマシだったぜ！」";
			link.l1 = "スヴェンソンを知ってるのか？";
			link.l1.go = "GonsalesB_1_2";
		break;
		
		case "GonsalesB_1_2":
			dialog.text = "くたばれ、スヴェンソンもくたばれ、あいつなんざ地獄にでも送っちまえ。森の悪魔でも海の悪魔でも、 俺にはどうでもいいんだ。病人の俺を助ける気がなくてカットラスも買わねえってんなら、 タダでてめえのケツにぶち込んでやるぜ。";
			link.l1 = "本当かよ？どうやってやるつもりだ、このクソ野郎！";
			link.l1.go = "GonsalesB_1_fight";
		break;
		
		case "GonsalesB_1_fight":
			chrDisableReloadToLocation = true;
			DialogExit();
			LAi_group_MoveCharacter(NPChar, "EnemyFight");
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetCheck("EnemyFight", "Saga_KillGonsalesB");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.Trap = "true";
		break;
		
		case "GonsalesB_2_1":
			dialog.text = "お前さん、なかなか経験豊富な男だな！千ペソで渡してやるぜ。";
			link.l1 = "取引成立だ！";
			link.l1.go = "GonsalesB_2_2";
		break;
		
		case "GonsalesB_2_2":
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(pchar, "blade_10");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "カルタヘナにはこんなカトラスは二振りしかない――俺のと、灯台のアルバレス爺さんのやつだけだ。だが、あいつは絶対に手放さねえ。偽善者め、 元海賊の臭いは遠くからでも分かるぜ。あの刃は、あいつにとっちゃお守りみたいなもんさ。\nきっと可哀想な奴だ、忘れたくても忘れられねえことを悔やんでるんだろう。だから毎月教会に通ってるのさ、 眠れぬほど罪に苛まれてな。";
			link.l1 = "それに、あんたにも何か過去があるようだな。スヴェンソンが話してたのは、きっとあんたのことだろう。 もしカルタヘナで会ったら、よろしく伝えてくれって言われてたぜ。";
			link.l1.go = "GonsalesB_2_3";
		break;
		
		case "GonsalesB_2_3":
			dialog.text = "スヴェンソン？聞いたことねえな。俺の名前はエンリケ・ガジャルドだ。でもよ、 お前のスヴェンソンがラム酒を一本持ってきてくれるなら、そいつのためにヘンリーになってやってもいいぜ。 好きなように呼んでくれよ、ただし晩飯に遅れるって呼ぶのは勘弁な。\nで、行くのか？";
			link.l1 = "今日は違うぜ。スヴェンソンは遠くにいるが、酒場はすぐそこだ。お前の懐ももう空っぽじゃねえ、気をつけろよ、 エンリケ。";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) link.l1.go = "GonsalesB_3_1";
			else link.l1.go = "GonsalesB_2_4";
		break;
		
		case "GonsalesB_2_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "19");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		// belamour участвовал в событиях Картахены -->
		case "GonsalesB_3_1":
			dialog.text = "でも、まだ全然満たされてねえんだ。もっと欲しい。お前が払うんだぜ。";
			link.l1 = "俺は呆れてるぜ……自分の命が惜しくねえのか？街中で俺を襲うつもりか？しかもさっき自分で俺に武器を売ったばかりだろうが？";
			link.l1.go = "GonsalesB_3_2";
		break;
		
		case "GonsalesB_3_2":
			dialog.text = "いいや、お前が自分で俺に払うんだ。なぜか分かるか？";
			link.l1 = "興味深い話だな。";
			link.l1.go = "GonsalesB_3_3";
		break;
		
		case "GonsalesB_3_3":
			dialog.text = "お前を見覚えがあるぜ。俺は酒場で酔っ払って乱闘して、地下牢にぶち込まれてたんだが、 そしたらお前の仲間たちが刑務所に押し入って看守どもを皆殺しにしたんだ。 俺はなんとか鍵を持ってた看守の死体までたどり着いて、通りに出られた。街は火の海、死体に血、 火薬の煙がそこら中に立ち込めててよ……まるで白兵戦の真っ最中みたいだったぜ！その煙の向こうから、お前が総督邸から出てくるのを見たんだ。詩的だろ？ ヨーホーホー、やあ、チャーリー・プリンス！";
			link.l1 = "そんなに怒鳴るな！お前が知ってることを考えれば、なおさら俺から金を巻き上げようなんてするべきじゃねえだろ。 俺が何をできるか、わかってんのか？";
			link.l1.go = "GonsalesB_3_4";
		break;
		
		case "GonsalesB_3_4":
			dialog.text = "かつてお前が盗みに入ったこの町のど真ん中でか？お前には何もできやしないさ。さて、まとめると……こうしよう。今すぐ俺に……そうだな、一万ペソ渡せ。それで一ヶ月は十分だろう。あとは好きにしな！愛しのヘンリーの元でも、 スヴェンソンの所でも、他の悪魔の所でも……好きに行けよ。だが、もし断るなら、俺が一声叫ぶだけで、 お前は拷問道具でいっぱいの特別な個室に引きずり込まれることになるぜ。";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "くそっ、さっさと一万持って俺の前から消えろ！それと、二度と俺の前に現れるんじゃねえぞ。";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "もういい加減にしろ。お前の武器は俺のものだ、だからお前に勝ち目はねえぞ、クズが。";
			link.l2.go = "GonsalesB_3_7";
			link.l3 = "ははっ、やるじゃねえか！なあ、知ってるか？他の奴ならもう腹から喉まで切り裂いてるところだぜ。でもな、 お前みたいな奴は俺に必要なんだ。どうだ、こうしよう――一万ペソやる、『ハングドマン』も返してやる。さらに毎月三千ペソもつけてやる――酒代には十分だろう――その代わり、俺の船の乗り組みになるってのはどうだ？\n";
			link.l3.go = "GonsalesB_3_9";
		break;
		
		case "GonsalesB_3_5":
			dialog.text = "わかった、わかったよ、もう行くって！捜索がうまくいくといいな、チャーリー王子！";
			link.l1 = "...";
			link.l1.go = "GonsalesB_3_6";
		break;
		
		case "GonsalesB_3_6":
			AddMoneyToCharacter(pchar, -10000);
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "191");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega();
		break;
		
		case "GonsalesB_3_7":
			dialog.text = "衛兵！衛兵！！チャーリー・プリンスだ！！！";
			link.l1 = "この野郎！";
			link.l1.go = "GonsalesB_3_8";
		break;
		
		case "GonsalesB_3_8":
			DialogExit();
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			LAi_group_AttackGroup("Spain_citizens", LAI_GROUP_PLAYER);
			npchar.lifeday = 0;
			AddQuestRecord("Saga", "192");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
		break;
		
		case "GonsalesB_3_9":
			dialog.text = "俺にお前の船員になれって言うのか？";
			link.l1 = "その通りだ。だが、これは一度きりの提案だぜ。どうする？同意するか、それともお前の腹をぶちまけてやろうか。 チャーリー・プリンスをそんな簡単に脅せると思ってんじゃねえだろうな？";
			link.l1.go = "GonsalesB_3_10";
		break;
		
		case "GonsalesB_3_10":
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 34 && makeint(pchar.reputation.nobility) < 48)
			{
				dialog.text = "悪魔め！チャーリー・プリンス本人が俺を自分のクルーに誘ってくれるなんてな！くそっ、承知したぜ！ 俺の剣と一万ペソを返してくれ。まさかこんな展開になるとは思わなかったぜ！";
				link.l1 = "ほら。あと、口をつぐんでろよ。この街の誰にも俺が誰かは知られたくねえ、わかったか？";
				link.l1.go = "GonsalesB_3_11";
				break;
			}
			if(makeint(pchar.reputation.nobility) > 47)
			{
				dialog.text = "いやだね。あんたは悪くない船長かもしれねえが、どうも堅物すぎる気がするぜ。確かに、 昔カルタヘナに大胆な襲撃を仕掛けてスペイン野郎どもを震え上がらせたことはあるが――あれも全部マーカス・タイレックスの助けがあってのことだろ。自分一人で堂々と略奪する度胸なんざ、 あんたにはねえよ。だから、とっとと金を出しな！\n";
			}
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
			{
				dialog.text = "いや、お前は確かに悪名高い海賊だが、船長としては大したことないな。 マーカス・タイレックスの助けがなければ植民地を略奪することもできなかったじゃねえか――自分一人じゃボロ船にも乗り込む度胸もねえだろう。だから、とっとと金を出しやがれ！";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "くそっ、さっさと一万持って俺の前から消えろ！それと、二度と俺の前に現れるんじゃねえぞ。";
				link.l1.go = "GonsalesB_3_5";
			}
			link.l2 = "もういい加減にしろ。お前の武器は俺のものだ、だからお前に勝ち目はねえぞ、このクズが。";
			link.l2.go = "GonsalesB_3_7";
		break;
		
		case "GonsalesB_3_11":
			dialog.text = "承知した、俺は馬鹿じゃねえ。";
			link.l1 = "よろしい。";
			link.l1.go = "GonsalesB_3_12";
		break;
		
		case "GonsalesB_3_12":
			DialogExit();
			AddMoneyToCharacter(pchar, -10000);
			LAi_RemoveLoginTime(npchar);
			npchar.quest.OfficerPrice = 3000;
			npchar.reputation.nobility = 30;
			npchar.dialog.FileName = "Enc_Officer_dialog.c";
			npchar.loyality = MAX_LOYALITY;
			GiveItem2Character(npchar, "blade_10");
			EquipCharacterByItem(npchar, "blade_10");
			TakeItemFromCharacter(pchar, "blade_10");
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			AddQuestRecord("Saga", "193");
			pchar.questTemp.Saga = "ortega";
			Saga_SetOrtega(); 
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
		break;
		// <-- участвовал в событиях Картахены
		
		//настоящий Гонсалес - Ортега, маяк
		case "Ortega":
			dialog.text = "私は誰の訪問も期待していない、今日もこれからもだ。何の用だ？";
			link.l1 = "やあ、首吊り人。森の悪魔に頼まれて来たんだ。ジャックマンの手下どもより先にお前を見つけられて運が良かったな。 奴の連中はカリブ中でお前を探してるぜ。ヘンリー、お前にとって幸運だったのは、 スヴェンソンだけがお前の生まれを知ってるってことさ。彼が俺にお前へ警告するよう頼んだんだ。";
			link.l1.go = "Ortega_1";
		break;
		
		case "Ortega_1":
			dialog.text = "なるほど……そうか、スヴェンソンはまだ生きていて、昔の友を忘れていないらしいな。あいつを初めて見たのは、 損傷したブリッグの甲板に立つ新米の頃だった……あれから多くの血が流れた。人生はあまりにも早く過ぎ去り、もう私には残された時間が少ない\n人里離れたこの荒れ地で、海のそばで、自然死を迎えたかった。しかしジャックマンがカリブに戻ってきたのなら、 私を放ってはおかないだろう。私のせいじゃなかったが、奴の主人には借りがある。だが、 今さら誰が私の言い分を信じるだろうか\n私が恐れているのは死ではなく、痛みだ。そしてジャックマンは痛みについてよく知っている。 そのことを考えるだけで心臓が止まりそうになり、すべてが暗くなっていく。";
			link.l1 = "ブッチャーは二十年前に絞首刑になったから、もう誰にも借金を返す必要はねえよ。ジャックマンが怖いなら、その借金、 俺に引き継いでもいいぜ。どうせ遅かれ早かれ、あんたもあいつに会うことになると思うがな。";
			link.l1.go = "Ortega_2";
		break;
		
		case "Ortega_2":
			dialog.text = "ブッチャーのような奴を絞首刑にするのは簡単じゃねえ。\nセント・ジョンズの元死刑執行人なら、地獄から戻ってきた死人について面白い話をいくらでも聞かせてくれるだろうさ。 \nそれに、ジェイコブは船長からしっかり仕込まれてる。だから、俺は一体どっちを恐れるべきか分からねえんだ。";
			link.l1 = "「なぜジャックマンはお前を必要としているんだ？」";
			link.l1.go = "Ortega_3";
		break;
		
		case "Ortega_3":
			dialog.text = "俺は未亡人に金を届けなきゃならなかったんだ、ブッチャーの娘を守ってくれた礼としてな。\nなんだよ、その目は？ああ、そうさ、あの娘は「ネプチューン号」が沈む少し前に生まれたんだ。 奴は戻ってこれなかったから、俺に赤ん坊と世話役の面倒を頼んできたってわけさ。";
			link.l1 = "グラディス・チャンドラーが管理人の名前だったのか？";
			link.l1.go = "Ortega_4";
		break;
		
		case "Ortega_4":
			dialog.text = "馬鹿な真似はやめろ。ジャックマンが俺を探しているのは、屠殺人の娘が必要だからだろう。 あんたももう知ってるはずだ、彼がベリーズ出身のグラディスという女とその養子を探していることを。正直に話せば、 俺もあんたを信じてやるかもしれない。";
			link.l1 = "グラディスに何を伝えることになっていたんだ？";
			link.l1.go = "Ortega_5";
		break;
		
		case "Ortega_5":
			dialog.text = "何もない。俺は彼女にブッチャーの指輪を見せるはずだった、それが船長からの使者だと分かる合図だったんだ。 それに赤ん坊のためのドゥブロン金貨の箱も渡すことになってた。 指輪を手に入れるためにクソ野郎を殺す羽目になってな。そのせいでアンティグアにもう一ヶ月も足止めされたんだ。\nようやくベリーズに着いた時には、グラディスはもういなくて、町はスペイン人に焼かれ略奪されていた。 彼女は家を売り払って、新しい男と赤ん坊のヘレンを連れて逃げたらしい。 あの子のことをちゃんと世話してくれていればいいが、ジプシーや売春宿に売り飛ばしてなきゃいいがな。";
			link.l1 = "「肉屋の娘の名前はエレンだったよな？」";
			link.l1.go = "Ortega_6";
		break;
		
		case "Ortega_6":
			dialog.text = "その通りだ。ブッチャーの母親への敬意としてな。もし生ける屍や死んだ目で睨んでくる海賊どもが怖くねえなら、 指輪と金貨をお前に渡してやる。俺は一度も手を付けちゃいねえ。飢え死にしかけてても、決して触らなかった。 好きにしな。\nその代わり、俺が頼みたいのは…";
			link.l1 = "何が起きているんだ、ヘンリー！？";
			link.l1.go = "Ortega_7";
		break;
		
		case "Ortega_7":
			dialog.text = "おまえ……お、おれは……た、たずね……ああっ！";
			link.l1 = "「いやだ！」";
			link.l1.go = "Ortega_8";
		break;
		
		case "Ortega_8":
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			AddQuestRecord("Saga", "20");
			pchar.questTemp.Saga = "svenson1";
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "bucher_ring"); //перстень Бучера
			//таймер на возврат смотрителя
			SetFunctionTimerCondition("Saga_LightmanReturn", 0, 0, 10, false);
			//ставим прерывания, если ГГ наследил в городе
			if (CheckAttribute(pchar, "questTemp.Saga.Trap"))
			{
				pchar.quest.Saga_Trap.win_condition.l1 = "location";
				pchar.quest.Saga_Trap.win_condition.l1.location = "Mayak11";
				pchar.quest.Saga_Trap.function = "Saga_CreateTrapBandos";
				TraderHunterOnMap(true);
			}
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			
			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs");
			//pchar.questTemp.HelenDrinking = "end_henry";
		break;
		
		//бандиты в поисках Гонсалеса, маяк
		case "saga_trap":
			dialog.text = "あっ、あそこにいるのは我らが好奇心旺盛な友だちじゃねえか！ゴンザレスをついに見つけたのか？よくやったな、 これで奴の居場所が分かった……もうお前は用済みだ。\n野郎ども、この道化を始末しろ！";
			link.l1 = "死ぬ時が来たぜ、カニのクズども！";
			link.l1.go = "saga_trap_1";
		break;
		
		case "saga_trap_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			int n = makeint(MOD_SKILL_ENEMY_RATE/3);
			for (i=1; i<=3+n; i++)
			{	
				sld = characterFromId("sagatrap_sold_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		//<-- поиск Гонсалеса, Картахена
		
//--------------------------------------------НПС по квесту Возвращение барона---------------------------------
		
		// доминиканский вождь
		case "DominicaHead":
			dialog.text = "ウアー！ウアー！偉大なるククルカンが新たな生贄を求めておられる！オエー！過去の偉大な戦士の魂が我らの村に現れ、 偉大なるククルカンへの生贄となるのだ！オエー！皆、偉大なる戦士の魂にひれ伏せ！";
			link.l1 = "（かすかに）なんだよここは、俺はどこにいるんだ？";
			link.l1.go = "DominicaHead_1";
			NextDiag.TempNode = "DominicaHead";
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("A Comanche potion is used", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("You are feeling that your health is restored!", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "DominicaHead_1":
			dialog.text = "おおえー！偉大なる戦士よ、偉大なるククルカンに喰われることを望むのか！\n太陽が昇り、影が短くなる！偉大なるククルカンはまもなく目覚めるぞ！\n我らはお前を彼のもとへ連れて行く、偉大なる戦士よ、そしてお前は祖先たちの地を渡り歩き続けるのだ！";
			link.l1 = "（かすかに）ばかな……またククルカンか？おい、酋長、俺は敵じゃねえ！俺はここに……";
			link.l1.go = "DominicaHead_2";
		break;
		
		case "DominicaHead_2":
			dialog.text = "おおっ！偉大なる戦士が、ただちにククルカンへの生贄となることを望むと申しておる。\nああ、偉大なる戦士よ！我らは今ククルカンのもとへ向かい、その御前で待つぞ！\n戦士たちよ！祖先の魂をククルカンに捧げることは、我らにとってこの上なき名誉だ！";
			link.l1 = "（かすかに）バカめ……仕方ない、奴らと一緒に行くしかない。この格好じゃ、まだ襲われてないのが幸いだ、防ぐことなんてできやしない……";
			link.l1.go = "DominicaHead_3";
		break;
		
		case "DominicaHead_3":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "reload1_back", "Saga_DominicaDollyReload", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;
		
		case "DominicaHead_4":
			dialog.text = "我々はククルカン、偉大なる祖霊のもとへ参る。\nまもなく太陽が沈み、影が伸び、ククルカンが我々を訪れるだろう。\n待て、偉大なる戦士よ……";
			link.l1 = "（かすかに）今わかったぞ、インディアンの戦士長……";
			link.l1.go = "DominicaHead_5";
		break;
		
		case "DominicaHead_5":
			DialogExit();
			bDisableCharacterMenu = true;//лочим Ф2
			AddQuestRecord("BaronReturn", "7");
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_DominicaDollyWait", 5.0);
			pchar.questTemp.Saga.BaronReturn = "third_teleport";
		break;
		
		case "DominicaHead_6":
			dialog.text = "ククルカンは生きている！ククルカンは我らと共にある！偉大なる戦士をククルカンへの生贄にできるぞ！\n戦士たちよ、偉大なる祖霊の前にひれ伏せ！";
			link.l1 = "（かすかに）近寄らないで、親分。自分でやるよ。これが初めてじゃないんだ……";
			link.l1.go = "DominicaHead_7";
		break;
		
		case "DominicaHead_7":
			DialogExit();
			bDisableCharacterMenu = false;//разлочим Ф2
			AddQuestRecord("BaronReturn", "8");
			for (i=2; i<=10; i++)
			{
				sld = characterFromId("Dominica_ind_"+i);
				LAi_SetActorType(sld);
			}
		break;
		
//----------------------------------------НПС по квесту Искушение Барбазона----------------------------------
		// капитан рыболовного баркаса, стыривший шелк, море
		case "BarbCapBarkas":
			dialog.text = "「どうなさいました、旦那？」";
			link.l1 = "ほうほう……で、相棒、ここで何してやがるんだ？";
			link.l1.go = "BarbCapBarkas_1";
		break;
		
		case "BarbCapBarkas_1":
			dialog.text = "俺はここで何してるかって？漁師だから、ここで魚を獲ってるんだよ。\nそれにしても、なんでそんな口調で俺に尋問してくるんだよ、まったく。";
			link.l1 = "俺に嘘つくんじゃねえ、相棒。お前が本当に漁師かもしれねえが、ここで漁なんかしてねえだろう。 高価な船の絹がこの場所で海に捨てられたんだ。そしてお前がここにいるだけで、俺には十分怪しく見えるぜ。";
			link.l1.go = "BarbCapBarkas_2";
		break;
		
		case "BarbCapBarkas_2":
			dialog.text = "何を馬鹿なことを言ってるんだ？どの絹の話をしてるんだ？";
			link.l1 = "何の絹だって？中国のやつだよ……とぼけるんじゃねえ！よく聞け、今すぐ船倉から絹を持ってきて俺に渡すか、それとも俺が自分で取りに行くかだ。 だがその前に、俺の乗り込み隊がてめえと船員どもを片付けるぜ。どうする？野郎どもを呼ぶか？";
			link.l1.go = "BarbCapBarkas_3";
		break;
		
		case "BarbCapBarkas_3":
			dialog.text = "いや！旦那、知らなかったんだ……あの俵はただ漂っていただけだから、俺はつい……";
			link.l1 = "絹を俺の船に運べ。急げ！";
			link.l1.go = "BarbCapBarkas_4";
		break;
		
		case "BarbCapBarkas_4":
			dialog.text = "はいはい、もちろんだ。すぐにやるから、俺のボートだけは取らないでくれよ！";
			link.l1 = "さっさと動けよ！俺にはあまり時間がねえんだ…";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_BarbBarkasSilk");
		break;
		
		case "BarbCapBarkas_5":
			dialog.text = "ほら、見つけたものは全部ここに持ってきた――九梱全部だ。これで全部だ、誓うよ……";
			link.l1 = "よし。釣りは続けていいが、これからは他人の持ち物に手を出すんじゃねえぞ！";
			link.l1.go = "BarbCapBarkas_6";
		break;
		
		case "BarbCapBarkas_6":
			DialogExit();
			npchar.DontDeskTalk = true;
			npchar.lifeday = 0;
			LAi_SetStayType(npchar);
			pchar.quest.BarbBarkas_Sink.over = "yes"; //снять прерывание
			pchar.quest.BarbBarkas_Abordage.over = "yes"; //снять прерывание
			NextDiag.CurrentNode = "BarbCapBarkas_7";
			AddQuestRecord("BarbTemptation", "6");
			pchar.questTemp.Saga.BarbTemptation = "give_silk";
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
		break;
		
		case "BarbCapBarkas_7":
			dialog.text = "お前はもう欲しいものを手に入れただろう。俺にはもう何も残ってねえ！まだ何を望むんだ？";
			link.l1 = "落ち着けよ、相棒。俺はもう行くぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "BarbCapBarkas_7";
		break;
		
		// Моррель, капитан потопленного судна, тюрьма
		case "Morelle":
			dialog.text = "もしバルバゾンに頼まれて来たのなら、あいつに伝えてくれ。俺は自分から牢を出たくない。裁判を待つ方がマシだ。 オランダの麻縄で首を吊られる方が、あいつの親切よりまだマシだからな。";
			link.l1 = "調子に乗るなよ。お前の航海士がジャックにお前は死んだと言ったんだ。 ジャックはお前が海に投げ捨てた絹を探せと俺に言いつけた。お前のブリガンティンにはどれくらい積んでいたんだ？";
			link.l1.go = "Morelle_1";
		break;
		
		case "Morelle_1":
			dialog.text = "俺のせいだ、くそっ。バルバゾンのために運び屋が絹の俵を九つ持ってきたんだ。俺はそいつを追わせた。だが、 奴が騒ぎ出したから、仕方なく喉を掻き切った。奴の隠し場所には余分に三つの俵があって、 それを俺が自分の隠し場所に移したんだ。だが、どうやら余計な注目を集めちまったらしい。\nすぐに見つかって、オープンウォーターで『ソルトドッグ』を待ち伏せてたのはオランダの哨戒隊だった。 逃げ切れなかったよ。バルバゾンに俺のことを黙っててくれるなら、その絹はお前が持っていっていい。 隠し場所はグランケース・ビーチの行き止まり近く、石の間だ。もう俺には必要なさそうだからな。";
			link.l1 = "いいだろう。バルバゾンにはお前がまだ生きていることは言わないさ。やつについての噂が本当なら、 オランダ人に絞首刑にされた方がまだマシだぜ。あるいは運が良ければ、強制労働刑で済むかもな。";
			link.l1.go = "Morelle_2";
		break;
		
		case "Morelle_2":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			// тайник - модель
			//int m = Findlocation("Shore40");
			//locations[m].models.always.Roll = "Roll_of_rolls";
			//Locations[m].models.always.Roll.locator.group = "quest";
			//Locations[m].models.always.Roll.locator.name = "quest1";
			pchar.quest.Saga_MorelGoods.win_condition.l1 = "locator";
			pchar.quest.Saga_MorelGoods.win_condition.l1.location = "Shore40";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator_group = "quest";
			pchar.quest.Saga_MorelGoods.win_condition.l1.locator = "quest1";
			pchar.quest.Saga_MorelGoods.function = "Saga_SetMorelGoods";
			AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 200);//скрытность
		break;
		
		// Валет, брат Джекмана в Капстервиле
		case "valet":
			dialog.text = "俺は白鮫狩りがいつ始まるか知っている男を待っているんだ。";
			link.l1 = "狩りが始まった。";
			link.l1.go = "valet_1";
		break;
		
		case "valet_1":
			dialog.text = "やっと来たか！さて、よく聞け。ラ・ベガのマーカス・タイレックスに会いに行き、「セパレーター」 というブリガンティンがタークス島近くで襲撃され、今はサザンベイに隠れていると伝えろ。船長は重傷で、 乗組員たちは救援を待っている。お前は「セパレーター」の水夫を拾い上げ、彼からすべてを聞いた。だが、 そいつはもう死んでいる。それだけしか知らない、いいな？";
			link.l1 = "「それに俺が必要なのはなぜだ？そんなことでこんなに長く待たされたのか……」";
			link.l1.go = "valet_2";
		break;
		
		case "valet_2":
			dialog.text = "お前は仕事の報酬をもらってるんだ、質問するためじゃねえ。\nだが、お前の言う通りだ。警告しておくが、タイレックスはお前が本当のことを話してると確信するまで解放しねえぞ。\nだが全部わかれば、やつはたっぷり報酬を払うはずだ。もしそれができればな……";
			link.l1 = "俺の目をごまかそうってのか、旦那……どうして自分で礼を受けたくねえんだ？";
			link.l1.go = "valet_3";
		break;
		
		case "valet_3":
			dialog.text = "カランバ！お前の好奇心は気に入らねえ！そのくだらねえおしゃべり、いつか早死にの元になるぜ。";
			link.l1 = "ああ、時々俺は手に負えねえんだぜ。特に誰かが俺を騙そうとしてるのが見えた時はな。いいか、相棒、 これからは俺のルールでやるぜ。てめえの主人は誰だ、くそったれ？答えろ、さもねえと力ずくで吐かせるぞ！";
			link.l1.go = "valet_4";
		break;
		
		case "valet_4":
			dialog.text = "てめえ……この野郎！バルバゾンがこの仕打ちの報いを受けさせてやる、てめえの命もここで終わりだ、クソ喰らいめ！";
			link.l1 = "はっ！こうなると思ってたぜ。覚悟しろ、この野郎！";
			link.l1.go = "valet_5";
		break;
		
		case "valet_5":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_ValetDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "vensan":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				dialog.text = "チャーリー・プリンス？ここで何してるんだ？あっ、くそっ、お前だったのか！全部お前の仕業じゃねえか！";
				link.l1 = "落ち着け、バーニー。俺はお前の味方だ。待ち伏せは片付けたから、お前もお前の船ももう安全だ。";
				link.l1.go = "vensan_8";
			}
			else
			{
				dialog.text = "てめえ、何者だ！？どうやってここに来たんだ？今すぐ出て行け、俺の船には火薬が仕掛けてあるんだ。 岸にいる野郎どもが一発で吹き飛ばせるんだぞ。";
				link.l1 = "心配するな、旦那。岸での待ち伏せは片付けたぜ。あんたの船は今は安全だ、もちろん甲板でパイプに火をつけなきゃな。 名前は何てんだ？";
				link.l1.go = "vensan_1";
			}
		break;
		
		case "vensan_1":
			dialog.text = "ヴァンサン。ベルナール・ヴァンサンだ。で、お前の名前は？";
			link.l1 = "Captain "+GetFullName(pchar)+"……その縄を切って、お前を自由にしてやる……";
			link.l1.go = "vensan_2";
		break;
		
		case "vensan_2":
			LAi_SetStayType(npchar);
			dialog.text = "ああ……感謝いたします。どうお礼を申し上げればよいのでしょうか？";
			link.l1 = "まだ終わっていません、旦那。あなたの乗組員でまだ生きている者はいますか？";
			link.l1.go = "vensan_3";
		break;
		
		case "vensan_3":
			dialog.text = "俺の部下三十六人が貨物倉に閉じ込められてるんだ……";
			link.l1 = "奴らを解放して、すぐにここから立ち去れ。 ";
			link.l1.go = "vensan_4";
		break;
		
		case "vensan_4":
			dialog.text = "しかし…";
			link.l1 = "時間を無駄にするな、ベルナール。お礼は後でラ・ベガでいい……タイレックスも感謝してくれるかもしれないな。";
			link.l1.go = "vensan_5";
		break;
		
		case "vensan_5":
			dialog.text = "つまり、偶然ここに来たわけじゃねえのか？全部知ってたのか？";
			link.l1 = "ああ、知っていたよ。ジャックマンの企みとマーカスを殺す計画を突き止めることができたんだ。ああ、それと、 タイレックスにはじっとしているように言ってくれ。 あいつが余計なことをするとジャックマンが逃げちまうかもしれないからな。";
			link.l1.go = "vensan_6";
		break;
		
		case "vensan_6":
			dialog.text = "必ず伝えます！もう出発されますか？";
			link.l1 = "ああ。お前も急いだほうがいいぞ。";
			link.l1.go = "vensan_7";
		break;
		
		case "vensan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto2", "none", "", "", "", 5.0);
			Ship_SetTaskRunaway(SECONDARY_TASK, GetCharacterIndex("Cap_Vensan"), GetMainCharacterIndex());
			pchar.questTemp.Saga.BarbTemptation.Vensan_free = "true";
			if (!CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.vensan_attack"))
			{
				if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1) sld = characterFromId("Mary");
				else sld = characterFromId("Helena");
				sld.dialog.currentnode = "sea_bomb"; 
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			sld = characterFromId("Cap_Vensan");
			sld.lifeday = 1;
			sld.DontDeskTalk = true;
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "vensan_8":
			dialog.text = "本当か？すまない、兄さん…";
			link.l1 = "忘れろ。俺が縄を切ってお前を自由にしてやる。";
			link.l1.go = "vensan_9";
		break;
		
		case "vensan_9":
			LAi_SetStayType(npchar);
			dialog.text = "くそっ……手の感覚がねえ……";
			link.l1 = "バーニー、船に他の生存者はいるか？";
			link.l1.go = "vensan_10";
		break;
		
		case "vensan_10":
			dialog.text = "三十人が貨物倉に閉じ込められている……";
			link.l1 = "奴らを解放して、とっととここから失せろ。今すぐだ！";
			link.l1.go = "vensan_11";
		break;
		
		case "vensan_11":
			dialog.text = "しかし……";
			link.l1 = "すぐにラ・ベガへ向かえ。この混乱についてマルクスにすべて詳しく伝えるんだ。";
			link.l1.go = "vensan_12";
		break;
		
		case "vensan_12":
			dialog.text = "マーカスがあなたを寄越したのか？";
			link.l1 = "彼はやっていない。俺がある野郎の陰謀を暴いたんだ。そいつはこの策略でマーカスを排除しようとしていた。 今はマーカスに大人しくしていて、余計なことはしないように伝えてくれ……後で俺が自分で全部説明する。それと、もう俺に怒るのはやめてくれって伝えてくれよ。\n";
			link.l1.go = "vensan_7";
		break;
		
 //--------------------------------------НПС по Завещанию Шарпа--------------------------------------------------
		// Устрица, Поль Моллиган
		case "molligan":
			dialog.text = "俺の船で何の用だ、旦那？";
			link.l1 = "ごきげんよう、ポール。あなたの名前はポール・モリガンで間違いありませんね？";
			link.l1.go = "molligan_0";
		break;
		
		case "molligan_0":
			dialog.text = "はい、それは私です。どうなさいましたか？";
			link.l1 = "私の名前は "+GetFullName(pchar)+" 「それにヤン・スヴェンソンが俺を寄越した。」";
			link.l1.go = "molligan_1";
		break;
		
		case "molligan_1":
			dialog.text = "「ヤン？あっ、思い出したよ。もちろん！最近よく彼の家に来てるじゃないか。それで、ヤンは俺に何の用だ？」";
			link.l1 = "お前はそんなに急いでブルーヴェルドから出航しようとしてたな。 ヤンはお前の船にさらに二百セントナーのマホガニーを積み込んで、 ブリッジタウンのウィロビー卿に届けてほしいと言ってたんだ。\n船の準備をしておけ、俺の連中がマホガニーを積み込むからよ。";
			link.l1.go = "molligan_2";
		break;
		
		case "molligan_2":
			dialog.text = "マホガニーだと？ヤンがそう言ったのか？ふむ。それで、なぜ自分でバルバドスに運ばない？なぜ俺なんだ？";
			link.l1 = "お前がそこへ航海するからだ、俺は行かねえ。俺にはスヴェンソンからの急ぎの任務があるから、 ブリッジタウンまで行ってる暇はねえんだ。それに、ヤンは俺がウィロビー卿と取引するのを信用してねえし、 お前に任せたいんだ。悪いな。さあ、積み込みを始めよう、俺はもう行かなくちゃならねえ。";
			link.l1.go = "molligan_3";
		break;
		
		case "molligan_3":
			dialog.text = "聞いてくれ、俺の貨物室にはもう空きがないんだ。ヤンの頼みを聞いてやりたいが、これじゃ無理だ。";
			link.l1 = "部屋がない？おかしいな……ヤンが空きがあるって言ってたぞ。";
			link.l1.go = "molligan_4";
		break;
		
		case "molligan_4":
			dialog.text = "確かにそうだが、ヤンは俺が「オイスター」にもっと重い大砲を積んだことを知らなかったんだ。 もうこれ以上荷物は積めねえよ。だから木材は自分でバルバドスまで運べ、相棒。 ヤンには俺には無理だったと伝えてくれ。ウィロビーの相手は簡単だぜ。会って、荷物を渡して、 領収書を受け取るだけだ。簡単だろう。";
			link.l1 = "ふむ。これは俺の予定じゃなかったが……さて、積荷室を見せてもらおうか？俺の四分士は荷物の積み込みが得意でな、きっとお前の積荷室に商品を詰め込んで、 しかも少し余裕まで残してくれるぜ……";
			link.l1.go = "molligan_5";
		break;
		
		case "molligan_5":
			dialog.text = "相棒、これ以上荷物は積めねえよ。俺に大砲を捨てさせて「オイスター」を丸腰にしろってのか？\n";
			link.l1 = "そうかい、そこまで自信があるならな……だがヤンは気に入らねえだろうぜ、そのことを忘れるなよ！";
			link.l1.go = "molligan_6";
		break;
		
		case "molligan_6":
			dialog.text = "スヴェンソンには俺が説明してやる、心配すんな。結局のところ、あいつのせいだ――俺の船のトン数について聞かなかったんだからな。";
			link.l1 = "ちぇっ、これでバルバドスまであの丸太どもと一緒に航海しなきゃならねえのか、くそっ……じゃあな、相棒。";
			link.l1.go = "molligan_7";
		break;
		
		case "molligan_7":
			DialogExit();
			// ставим проверку скрытности
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > (10+hrand(50)))
			{
				pchar.questTemp.Saga.Molligan.friend = "true"; // будет шанс критического залпа картечью
				sTemp = "The scoundrel is still not suspecting a thing. I should get closer and shoot at him with grapeshot. A sudden strike will always win in any battle. ";
				log_Testinfo("Friends");
				AddCharacterExpToSkill(pchar, "Fortune", 200);//везение
				AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			}
			else
			{
				pchar.questTemp.Saga.Molligan.enemy = "true"; // нападет
				sTemp = "";
				log_Testinfo("Enemies");
				AddCharacterExpToSkill(pchar, "Sneak", 150);//скрытность
			}
			AddQuestRecord("Testament", "7");
			AddQuestUserData("Saga", "sText", sTemp);
			NextDiag.CurrentNode = "molligan_8";
			npchar.DontDeskTalk = true; // patch-5
		break;
		
		case "molligan_8":
			dialog.text = "俺たちの間で話はついてるよな？";
			link.l1 = "ああ、ああ。俺は自分の船に行くところだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "molligan_8";
		break;
		
	//-----------------------------------------НПС по Теням прошлого--------------------------------------------
		// Джим Бенсон, плешивая мэгги
		case "benson":
			dialog.text = "俺に何の用だ？噂話も賭け事も興味ねえ。ラムも一人で飲む主義だ。\nそれに、前の航海のせいで機嫌が悪いんだよ。";
			link.l1 = "「さて、前回の航海で何か特別な出来事でもあったのか？」";
			link.l1.go = "benson_1";
		break;
		
		case "benson_1":
			dialog.text = "一人の善良な男が俺を信じてくれたが、乗組員が要求したから、俺はそいつを海に突き落としたんだ。";
			link.l1 = "「それで、彼の罪は何だったんだ？」";
			link.l1.go = "benson_2";
		break;
		
		case "benson_2":
			dialog.text = "俺はここじゃ新参者で、知り合いもほとんどいねえ。だから、あの心優しいデブを過去も知らずに船医として雇ったんだ。 バルバドスを出てからずっと、海賊どもが俺たちを追い回してやがる。あいつらが俺のボロ船を狙う理由が分からねえ。\nなんとか強い嵐のおかげで逃げ切った。祝いに一杯やったんだが、あのデブの馬鹿野郎は、よりによって 「自分は元死刑執行人で、知っちゃいけねえことを知ってるから海賊に狙われてるんだ」なんて、 みんなの前で言いやがった。\n当然、船員たちはブチ切れたさ。なあ、マジかよ！？死刑執行人が船医だなんて！誰も海賊と関わりたくねえし……仕方なく、あの哀れな奴を陸に降ろした。全部あいつのせいだ、余計なことを口にしやがって。でも田舎者のくせに、 あいつは腕のいい医者だったんだ。俺の二日酔いも、たった一分で治してくれたからな。";
			link.l1 = "くそっ！お前の医者の名前はレイモンド・ベイカーだったよな？";
			link.l1.go = "benson_3";
		break;
		
		case "benson_3":
			dialog.text = "ああ、その通りだ。で、どうして知ってるんだ？俺のことをつけてたのか？";
			link.l1 = "いや、俺じゃねえ。あの男が必要なんだ、腕のいい医者だからな。どこに上陸させた？";
			link.l1.go = "benson_4";
		break;
		
		case "benson_4":
			dialog.text = "北緯15度28分、西経63度28分だ。急いでくれ、旦那！まだ生きているはずだし、あんたが助けてくれれば俺の責任もなくなるんだ！\n";
			link.l1 = "もう錨を上げているぜ！";
			link.l1.go = "benson_5";
		break;
		
		case "benson_5":
			DialogExit();
			NextDiag.CurrentNode = "benson_6";
			AddQuestRecord("Shadows", "3");
			npchar.lifeday = 0;
			bQuestDisableMapEnter = false;
			pchar.quest.Saga_Shadows_Baker.win_condition.l1 = "location";
			pchar.quest.Saga_Shadows_Baker.win_condition.l1.location = "Dominica";
			pchar.quest.Saga_Shadows_Baker.function = "Saga_SetBakerBoat";
			DeleteAttribute(pchar, "Cheats.SeaTeleport");
		break;
		
		case "benson_6":
			dialog.text = "船長、急いでくれ！まだ生きてるはずだ！";
			link.l1 = "はいはい、今行くよ……";
			link.l1.go = "exit";
			NextDiag.TempNode = "benson_6";
		break;
		
	//---------------------------------------бандиты у джекмановского рудника-------------------------------
		case "mine_bandit":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "おい！そこにいろ！動くんじゃねえ。この領域は確保されてるぜ！";
				link.l1 = "あんまりきつくすんなよ、相棒！\nみんな！ジャックマンが俺たちを送ったんだ。\n鉱山に行く必要がある。親方の命令だ……";
				link.l1.go = "mine_attack";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "おい！そこにいろ！動くんじゃねえ。この領域は確保済みだ！";
				link.l1 = "ふん。でも俺は通りたいんだ…なんでお前は俺を止めるんだよ？";
				link.l1.go = "mine_bandit_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "あ、あんたか、また来やがったな？わかってねえみたいだな……野郎ども、撃て！！";
				link.l1 = "...";
				link.l1.go = "mine_bandit_fire";
			}
		break;
		
		case "mine_bandit_0":
			dialog.text = "さあ、進め！";
			link.l1 = "……わかった……";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_bandit_0";
		break;
		
		case "mine_bandit_1":
			dialog.text = "俺の後ろにある鉱山は私有地だ。だから、あんたみたいなよそ者が通るのを止めるためにここにいるんだ。 引き返してこの場所を離れた方がいいぜ、よそ者。\nうちの大砲にはブドウ弾が装填されてる。あと一歩でも踏み出せば、あんたは血まみれの水たまりになるぞ。";
			link.l1 = "へえ、そうか。お前の鉱山はしっかり守られてるんだな。\nよし、俺は引き上げるぜ。";
			link.l1.go = "mine_bandit_exit";
			link.l2 = "この野郎！さて、最後に水たまりになるのはどっちか見ものだぜ！";
			link.l2.go = "mine_bandit_2";
		break;
		
		case "mine_bandit_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestReloadToLocation("Mine_02", "reload", "reload3", "");
		break;
		
		case "mine_bandit_2":
			dialog.text = "チャンスはやったぜ……野郎ども、撃て！！";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_bandit_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsFire", 1.5);
		break;
		
		case "mine_banditx":
			locCameraFromToPos(6.21, 2.31, 8.46, true, -2.26, -1.10, 4.99);
			if (CheckAttribute(pchar, "questTemp.Saga.MineAttack"))
			{
				dialog.text = "おい！消え失せろ！ここは警備されてる場所だぞ！";
				link.l1 = "おい、落ち着けよ、相棒！ジャックマンが俺たちを寄越したんだ。鉱山に行く必要がある。親方の命令だぜ…";
				link.l1.go = "mine_attackx";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "おい！消え失せろ！ここはもう押さえてるんだ！";
				link.l1 = "ふむ。それで、そこには何があるんだ？";
				link.l1.go = "mine_banditx_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "あ、あんたか、また来やがったな？わかってねえみたいだな……野郎ども、撃て！！";
				link.l1 = "...";
				link.l1.go = "mine_banditx_fire";
			}
		break;
		
		case "mine_banditx_1":
			dialog.text = "お前には関係ねえ。さっさと失せろ、じゃねえと撃つぞ、誓ってな！";
			link.l1 = "落ち着け。俺はもう行く。";
			link.l1.go = "mine_banditx_exit";
			link.l2 = "この野郎！さあ、どっちが先に撃つか見ものだぜ！";
			link.l2.go = "mine_banditx_2";
		break;
		
		case "mine_banditx_exit":
			DialogExit();
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "PIRATE_CITIZENS");
			DoQuestReloadToLocation("Mine_04", "reload", "reload3", "");
		break;
		
		case "mine_banditx_2":
			dialog.text = "チャンスをやったのに……銃を構えろ！撃て！！";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_banditx_fire":
			DialogExit();
			DoQuestCheckDelay("Saga_MineBanditsxFire", 0.6);
		break;
		
		case "mine_attackx":
			dialog.text = "本当か？じゃあ、合言葉を知ってるはずだな。言ってみろ、嘘だったら後悔するぜ……";
			link.l1 = "Triton";
			link.l1.go = "mine_wrongx_password";
			link.l2 = "Neptune";
			link.l2.go = "mine_attackx_1";
			link.l3 = "Centurion";
			link.l3.go = "mine_wrongx_password";
			link.l4 = "Harpoon";
			link.l4.go = "mine_wrongx_password";
		break;
		
		case "mine_attackx_1":
			dialog.text = "その通りだ。だがな、相棒、お前は反対側から来ちまったんだよ。誰にも注意されなかったのか？ 戻って枯れ井戸のところから左の道を行け。それから丘を回り込めば、そこに正門が見えるはずだ。\n";
			link.l1 = "ここに入っちゃいけないのか？";
			link.l1.go = "mine_attackx_2";
		break;
		
		case "mine_wrongx_password":
			dialog.text = "おい野郎ども、探偵気取りが来やがったぞ！銃を構えろ！撃て！！";
			link.l1 = "...";
			link.l1.go = "mine_banditx_fire";
		break;
		
		case "mine_attackx_2":
			dialog.text = "いいえ。中央の入口からしか入れません。";
			link.l1 = "よし、相棒……おい！見ろよ！あの柵の上にあるのは一体なんだ！？";
			link.l1.go = "mine_attackx_3";
		break;
		
		case "mine_attackx_3":
			DialogExit();
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Mine_banditx_"+i);
				LAi_RemoveCheckMinHP(sld);
			}
			sld = characterFromId("Svensons_sold_12");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "soldiers", "soldier1");
			LAi_ActorAnimation(sld, "shot", "Saga_MineBanditxDie", 1.0);
		break;
		
		case "mine_attack":
			dialog.text = "本当か？じゃあ、合言葉を知ってるはずだな。聞こえるようにはっきり言ってみろ。もし俺を騙そうとしたら、 それが人生で最後の冗談になるぜ。";
			link.l1 = "Triton";
			link.l1.go = "mine_wrong_password";
			link.l2 = "Neptune";
			link.l2.go = "mine_attack_1";
			link.l3 = "Centurion";
			link.l3.go = "mine_wrong_password";
			link.l4 = "Harpoon";
			link.l4.go = "mine_wrong_password";
		break;
		
		case "mine_attack_1":
			dialog.text = "その通りだ。進め。キャンプの責任者は鉱山入口の左手の家にいる。会いに行け。";
			link.l1 = "「いいぜ、相棒…」";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_wrong_password":
			dialog.text = "おい野郎ども、探偵が来やがったぞ！大砲、撃て！！";
			link.l1 = "...";
			link.l1.go = "mine_bandit_fire";
		break;
		
		case "mine_attack_2":
			DialogExit();
			locCameraFollowEx(true);
			NextDiag.CurrentNode = "mine_attack_3";
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "ActorDialog_Any2Pchar", -1);
			LAi_ActorTurnToCharacter(npchar, pchar);
			SetActorDialogAny2Pchar(npchar.id, "", 0.0, 0.0);
		break;
		
		case "mine_attack_3":
			dialog.text = "他には？何か忘れてないか？";
			link.l1 = "はい。あなたに心からのご挨拶をお伝えするよう頼まれました。";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "俺にか？ははっ！誰からだ？";
			link.l1 = "「ヤン・スヴェンソン、この野郎！」";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			DialogExit();
			AddDialogExitQuestFunction("Saga_MineAttack");
		break;
		
	// ----------------------------- диалоги НПС при штурме бандитского рудника -------------------------------
		case "Svensons_off":
			dialog.text = LinkRandPhrase("あいつらをぶっ潰してやるぜ！","あのクズどもをぶちのめすのが楽しみだぜ！","ジャックマンの手下どもに西部本島にいる権利なんかねえ！俺たちがここから追い払ってやるぜ！");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_off";
		break;
		
		case "Svensons_sold":
			dialog.text = LinkRandPhrase("俺たちは戦う準備ができてるぜ！","見せてやるぜ！","奴ら、自分たちが誰に手を出してるのか分かっちゃいねえんだぜ！");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Svensons_sold";
		break;
		
		case "gunner":
			PlaySound("Voice\English\evilpirates01.wav");
			dialog.text = "司令官、大砲の準備ができました。ご命令通り爆弾を装填してあります。";
			link.l1 = "ここで俺たちを待ってる奴はいないようだな……そろそろ自己紹介といこうか。ヤンが言ってたが、あいつらの野営地はこの丘の向こうだ。たどり着けそうか？\n";
			link.l1.go = "gunner_0_1";
		break;
		
		case "gunner_0_1":
			dialog.text = "簡単なことだな、司令官。樽を少し上げてみよう、それでいけるはずだ……よし、できた。\n準備しろ！……撃て！！";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "1";
		break;
		
		case "gunner_0_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_Gunfire", 3.0);
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_1":
			dialog.text = "";
			link.l1 = "ふむ。ランドルフ、何かにぶつかったと思うか？君の意見を聞きたいんだ。";
			link.l1.go = "gunner_1_1";
		break;
		
		case "gunner_1_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "司令官、何かに、あるいは誰かに当たったのは確かですが、詳しくは分かりません……この忌々しい丘のせいで視界が悪いんです。角度を変えます。\n準備完了！撃て！";
			link.l1 = "...";
			link.l1.go = "gunner_0_2";
			npchar.quest.canonada = "2";
		break;
		
		case "gunner_2":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			dialog.text = "はっ！見ろよ、司令官！煙が上がってるぜ！くそっ、どうやら盗賊どもの納屋に命中したらしい！万歳だー！\n";
			link.l1 = "ああ、煙が見えるな……すでに壮大な勝利ってわけだ、間違いねえ。大砲を再装填して道に狙いをつけろ、どうやらお客さんが来るみたいだぜ。 きっちり歓迎してやろうじゃねえか！";
			link.l1.go = "gunner_2_1";
		break;
		
		case "gunner_2_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "了解だ、司令官！爆弾を装填しろ！砲手、準備！導火線、よし！俺の合図で撃て！";
			link.l1 = "...";
			link.l1.go = "gunner_2_2";
			npchar.quest.canonada = "3";
		break;
		
		case "gunner_2_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_01", 6.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_3":
			PlaySound("interface\abordage_wining.wav");
			PlaySound("types\warrior03.wav");
			PlaySound("Voice\English\evilpirates05.wav");
			dialog.text = "ははっ、こりゃ痛ぇだろうな！";
			link.l1 = "まだ気を抜くな！砲を装填しろ！あいつらはまだ懲りてねえみたいだ。もっと来るぞ！";
			link.l1.go = "gunner_3_1";
		break;
		
		case "gunner_3_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");//
			dialog.text = "了解だぜ、司令官！爆弾を装填しろ！準備完了！俺の合図で撃て！";
			link.l1 = "...";
			link.l1.go = "gunner_3_2";
			npchar.quest.canonada = "4";
		break;
		
		case "gunner_3_2":
			DialogExit();
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("Saga_LoginBandos_02", 5.0);
			LAi_ActorTurnToLocator(pchar, "goto", "goto14");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
		break;
		
		case "gunner_5":
			PlaySound("types\warrior04.wav");
			PlaySound("Voice\English\evilpirates06.wav");
			dialog.text = "ハハハ、野郎どもが尻尾を巻いて逃げやがった！犬の餌だぜ！この距離ならブドウ弾でバラバラだ！ もう一度俺たちに攻撃する度胸はねえみたいだな！\n";
			link.l1 = "今度は俺たちの番だ。ランドルフ、お前はここで大砲のそばにいろ。道に向かって何発か撃ったら、煙を狙え――奴らの巣を焼き払え！ただし、俺たちに撃つんじゃねえぞ。";
			link.l1.go = "gunner_5_1";
		break;
		
		case "gunner_5_1":
			PlaySound("interface\" + LanguageGetLanguage() + "\_bombs_npc.wav");
			dialog.text = "了解だぜ、司令！大砲を用意しろ！弾を込めろ！\n";
			link.l1 = "野郎ども！武器を取れ！俺について来い、攻撃だ！おおっしゃあ！！";
			link.l1.go = "attack";
		break;
		
		case "attack":
			DialogExit();
			n = Findlocation("mine");
			Locations[n].hidden_fire = true;
			PlaySound("interface\abordage_wining.wav");
			PlaySound("interface\abordage_wining.wav");
			LAi_ActorTurnToLocator(npchar, "goto", "goto14");
			LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
			if (GetCharacterIndex("Svensons_sold_12") != -1 && pchar.questTemp.Saga.MineAttack == "soldiers")
			{
				sld = characterFromId("Svensons_sold_12");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=8; i++)
			{
				if (GetCharacterIndex("Ourmine_sold_"+i) != -1)
				{
					sld = characterFromId("Ourmine_sold_"+i);
					if (i == 1) sld.MusketerDistance = 10; 
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			LAi_group_SetRelation("EnemyFight", "TMP_FRIEND", LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_MineBandos_05Die");
			AddDialogExitQuest("MainHeroFightModeOn");	
			DoQuestCheckDelay("Saga_MineSetMusic", 0.3);
			// запускаем автобабахалку на 10 выстрелов
			iTotalTemp = 0;
			DoQuestCheckDelay("Saga_GunAutoFire", 7.0);
			bDisableCharacterMenu = false;//разлочим интерфейсы
			InterfaceStates.Buttons.Save.enable = true;//разрешим сохраняться
		break;
		
		case "convict":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = LinkRandPhrase("俺を傷つけないでくれ、俺はあいつらの仲間じゃねえ！山賊どもをやっちまえ！","助けてくれ、相棒！そいつらを皆殺しにしてくれ！","斬れ、相棒、斬っちまえ！ぶっ殺せ！");
				link.l1 = "ははっ！心配するな、まさに今それをやってるところだぜ。";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = LinkRandPhrase("俺たちの奴隷生活は終わったのか？俺たちを自由にしてくれるのか？","へっ、俺は本当にこの日まで生き延びちまったのか？","野郎どもに血を全部吸い取られちまった……。");
				link.l1 = "もうすぐ自由を満喫できると思うぜ、相棒…";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "convict";
		break;
		
		// жена Яна Свенсона
		case "js_girl":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = "ここは早く立ち去ったほうがいいぞ、旦那。うちは犯罪者を匿ったりしねえし、植民地の役人と揉め事なんざごめんだ。";
				link.l1 = "……わかった、俺は行くぜ……";
				link.l1.go = "exit";
				NextDiag.TempNode = "js_girl";
				break;
			}
			if(NPChar.quest.meeting == "0")
			{
				// Первый диалог с Элен
				if(startHeroType == 4)
				{
					dialog.text = "ああ、エレン。ヤンに会いに来る前に、もう少しまともな格好をしてくればよかったのに。本当のお前を見せるなんてな。 残念だが、ヤンは俺の言うことを信じてくれないんだよな。";
					link.l1 = "で、私は一体どんな人間だって言うの？あの人は子供の頃から私を育ててくれて、誰よりも私のことを知っているのよ。 私にはあの人に隠し事なんてないわ。私は子供の頃からこの暑さに苦しんできたから、 自分なりのやり方で対処するしかなかっただけよ、それだけ。";
					link.l1.go = "js_helen_ft";
					NextDiag.TempNode = "js_girl";
					NPChar.quest.meeting = "1";
					break;
				}
				dialog.text = TimeGreeting()+"、旦那。ヤンに会いたいですか？";
				link.l1 = "ごきげんよう。お会いできて光栄です、お嬢様……？ ";
				link.l1.go = "js_girl_1";
			}
			else
			{
				// заглушка элен
				if(startHeroType == 4)
				{
					dialog.text = "ヤンは中にいるぜ。さあ、進みな。ここには何も見るものはねえし、お前、俺の神経を逆なでしてるんだよ。";
					link.l1 = "どうせその気じゃなかったんだ。";
					link.l1.go = "exit";
					NextDiag.TempNode = "js_girl";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Joan")) {
					dialog.text = "ううっ！";
					link.l1 = "「あなたもお元気で、スヴェンソン夫人。」";
					link.l1.go = "exit";
					break;
				}
				
				if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
				{
					dialog.text = TimeGreeting()+"「船長」 "+GetFullName(pchar)+"。もしヤンに用があって来たのなら、残念だがここにはいないぜ。大事な用事で出かけてるんだ。";
					link.l1 = "くそっ！俺にはあいつが必要なんだ！スヴェンソン夫人、彼がいつ戻るか聞いていましたか？";
					link.l1.go = "js_girl_3";
					break;
				}
				dialog.text = "あ、またあなたか、船長 "+GetFullName(pchar)+"「…さあ、進んでくれ。ヤンはいつも通り二階にいるぜ。」";
				link.l1 = "ありがとうございます、スヴェンソン夫人……";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_1":
			dialog.text = "奥様、ヨハンナ・スヴェンソン奥様。";
			link.l1 = "Captain "+GetFullName(pchar)+".";
			link.l1.go = "js_girl_2";
		break;
		
		case "js_girl_2":
			if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "blueveld")
			{
				dialog.text = "船長？まあ、私の家へようこそお越しくださいました。\nですが、ヤンに用があって来られたのでしたら、残念ですがご期待に添えません――彼はここにはいません。\n大事な用事で出かけております。";
				link.l1 = "くそっ！あいつが必要なんだ！スヴェンソン夫人、彼はいつ戻ると言っていましたか？";
				link.l1.go = "js_girl_3";
				break;
			}
			dialog.text = "船長？まあ、私の家へようこそ。\n夫は二階の書斎におります。\nどうぞ二階へお上がりください。";
			link.l1 = "承知しました、スヴェンソン夫人……";
			link.l1.go = "exit";
			NPChar.quest.meeting = "1";
			NextDiag.TempNode = "js_girl";
		break;
		
		case "js_girl_3":
			dialog.text = "いいえ。彼は自分でも捜索がどれだけ続くか分からないから、帰還の日付すら正確には教えてくれませんでした。";
			link.l1 = "お邪魔して申し訳ありませんが、どうしても彼が必要なんです……彼は一体どんな捜索をしているのですか？";
			link.l1.go = "js_girl_4";
		break;
		
		case "js_girl_4":
			dialog.text = "教えてやろう。あの可憐なヘレン――ルンバとも呼ばれているが――彼の亡き友ショーン・マッカーサーの娘が行方不明になったんだ。 ヤンはあの小悪魔をまるで自分の娘のように扱っている。彼女は、かつての恋人を思い出させるらしい、 同じ向こう見ずな気性だったそうだ。少なくとも、それがヤンが惹かれる理由だと俺は思うぜ。\nともかく、その娘は一週間前に自分のスクーナー『レインボー』と乗組員ごと消えちまった。 ショーン・マッカーサーが彼女に航海術を教え、『レインボー』も遺言で譲ったんだ。そして今じゃ、 彼女は自分を船長だと名乗っている……";
			link.l1 = "彼女に何が起こったんだ？";
			link.l1.go = "js_girl_5";
		break;
		
		case "js_girl_5":
			dialog.text = "誰にも分からんさ……一週間なんて大した時間じゃねえが、マッカーサーの未亡人は娘に何かあったと信じ込んでて、 ヤンまでその気にさせちまった。ヤンは部下を集めて自分で捜索を始めたが、今のところ手がかりはなし。 俺は個人的にはヘレンは無事だと思うし、ヤンが勝手に自分を苦しめてるだけだと思うぜ。\nあの年増で太った女の戯言を真に受けすぎて、慌てふためいちまったんだろう。あの娘は今ごろ、 誰にも見つからねえ安全な場所で、別の男と楽しくやってるに違いねえさ。腹が減ったらすぐ戻ってくるさ。";
			link.l1 = "ジョアンナ、グラディスはどこにいる？彼女と話したいんだ…";
			link.l1.go = "js_girl_6";
		break;
		
		case "js_girl_6":
			dialog.text = "彼女の家は桟橋の近く、左側にある。\nだが、たぶん今はいないだろう。毎日砦の城壁に立って、大事な娘を探し続けているんだ。";
			link.l1 = "なるほど。ご情報ありがとうございます！";
			link.l1.go = "js_girl_7";
		break;
		
		case "js_girl_7":
			DialogExit();
			NextDiag.CurrentNode = "js_girl_8";
			sld = characterFromId("Gladis"); //устанавливаем Глэдис на форт
			ChangeCharacterAddressGroup(sld, "SantaCatalina_fort", "goto", "goto53");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "FindHelena";
			pchar.questTemp.Saga = "gladis";
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("SantaCatalina_tavernkeeper"));
			DelMapQuestMarkCity("SantaCatalina");
		break;
		
		case "js_girl_8":
			dialog.text = "ヤンはまだ来ていませんぜ、船長。だから、後でもう一度来てください。";
			link.l1 = "なるほど……";
			link.l1.go = "exit";
			NextDiag.TempNode = "js_girl_8";
		break;
		
		case "js_helen_ft":
			dialog.text = "お前はいつもムラムラしてるじゃねえか。教会にでも行ったらどうだ？お前がそこにいるのなんて、 ほとんど見たことねえぞ。";
			link.l1 = "私の良心は潔白だ――謝ることなんて何もないさ。\nそれとも、ヨアンナ、お前に新しいドレスを買う代わりに俺の船に物資を回したことが、まだそんなに気に食わねえのか？ ";
			link.l1.go = "js_helen_ft_1";
		break;
		
		case "js_helen_ft_1":
			dialog.text = "俺が？悔しがってるって？お前なんかにそんな価値はねえよ。ただな、お前は何もかも簡単に手に入れすぎなんだよ、 それにふさわしくもねえくせによ。";
			link.l1 = "だが、俺があの船を手に入れた途端、自分の力で稼ぎ始めたんだ。\nそれに、お前はあいつに野良猫みたいに拾われてから、一日たりとも働いてねえだろ。\nじゃあ、本当にあいつに寄生してるのは誰なんだ？";
			link.l1.go = "js_helen_ft_2";
		break;
		
		case "js_helen_ft_2":
			dialog.text = "そんな口をきいてると、いつか痛い目に遭うぞ。ヤンとグラディスに礼儀を叩き込まれてるはずだろうが。まあいい、 用があるならさっさと言え――それが済んだらとっとと俺の前から消えろ、ヘレン。あいつは中にいる。";
			link.l1 = "馬鹿な雌鶏だな。ああ、やってやるよ。";
			link.l1.go = "exit";
		break;
		
		// хронометр Алекса
		case "Alexs_bandos":
			dialog.text = "おい！ここで何してるんだ？";
			link.l1 = "俺も同じことを聞きたいぜ――お前と仲間たちは、俺の牢屋で何をしてやがるんだ？\n";
			link.l1.go = "Alexs_bandos_1";
		break;
		
		case "Alexs_bandos_1":
			dialog.text = "はっ！お前の牢屋だと？いつからお前のものになったんだ、この下衆め？";
			link.l1 = "お前の父親が母親と寝てしまったあの日さ。";
			link.l1.go = "Alexs_bandos_2";
		break;
		
		case "Alexs_bandos_2":
			dialog.text = "揉め事を探してるのか？";
			link.l1 = "聞けよ、相棒。ここを出て行く最後のチャンスをやるぜ。ここは俺の牢屋だ、勝手に入り込ませるわけにはいかねえんだ、 分かったか？俺が一声口笛を吹けば、イスラ・テソロの海賊の半分が一分もしねえうちにここに集まるんだぜ。";
			link.l1.go = "Alexs_bandos_3";
		break;
		
		case "Alexs_bandos_3":
			dialog.text = "じゃあ、お前の口を黙らせてやるぜ！";
			link.l1 = "ははっ！お前は情けねえな、クズ野郎！";
			link.l1.go = "Alexs_bandos_4";
		break;
		
		case "Alexs_bandos_4":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation("Bermudes_Dungeon")], false);
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("Alexs_bandos_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
			int iScl = 25+2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("Alexs_bandos_5", "mush_ctz_8", "man", "mushketer", iRank, PIRATE, -1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "", "mushket1", "bullet", iScl*2+50);
			ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AlexClock_BandosDie");
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "helendrinking_gypsy":
			dialog.text = "ちょっと待て、鷹野郎！";
			link.l1 = "「タイミングが悪いな、可愛い子ちゃん。」";
			link.l1.go = "helendrinking_gypsy_1";
		break;
		
		case "helendrinking_gypsy_1":
			dialog.text = "おや、勘違いしてるぜ、イケメン。この娘はあんたのことが好きなんだよ、 しかもあんたも同じ気持ちなのが見て取れるぜ。";
			link.l1 = "あまり良い推薦じゃないな……で、何が欲しいんだ？施しでも求めてるのか？";
			link.l1.go = "helendrinking_gypsy_2";
		break;
		
		case "helendrinking_gypsy_2":
			dialog.text = "あなたの困難な挑戦を支援したいんだ。\n見てくれ！魔法のマグカップと禁断の軟膏だ。\nマグカップは酒を飲むのに役立つし、軟膏は恋の悩みに効くぜ。\nどっちを選ぶ？たったの二千だ！";
			link.l1 = "俺は何もいらねえ――お前らの類にはもう山ほど銀をくれてやったんだ。";
			link.l1.go = "helendrinking_gypsy_refuse";
			if (sti(pchar.money) >= 2000) {
				link.l2 = "禁断の軟膏だと？まあ、俺は聖人じゃねえしな。よこしな。";
				link.l2.go = "helendrinking_gypsy_fuck";
				link.l3 = "ジョッキだと？俺が酔っ払いに見えるか？……まあ、冗談だ。もらっとくぜ！";
				link.l3.go = "helendrinking_gypsy_drink";
			}
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_refuse":
			dialog.text = "ハンサムだが愚か者だな。さあ、飛び立て、鷹よ。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_drink":
			dialog.text = "おいおい、そんな底なしのポケットに隠すなよ！飛んでいけ、鷹よ、悪さはするな！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_01");
			Log_Info("Talisman 'Throat of cast iron' acquired!");
			PlaySound("interface\important_item.wav");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_gypsy_fuck":
			dialog.text = "ああ、そんな底なしのポケットに隠すなよ！飛んでいけ、鷹よ、そして悪さはするな！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddMoneyToCharacter(pchar, -2000);
			GiveItem2Character(pchar, "totem_03");
			Log_Info("Talisman 'Cupid's Balm' acquired!");
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_TalkedToGypsy");
		break;
		
		case "helendrinking_joan":
			dialog.text = "あっ！出ていけ、このろくでなし！何度言ったら私の家にこっそり入るなと分かるんだ！それで、こいつは誰だ？";
			link.l1 = "奥様、私たちはすでに面識があります。";
			link.l1.go = "helendrinking_joan_1";
		break;
		
		case "helendrinking_joan_1":
			dialog.text = "ド・モール様？まあ、なんてこと！あなたは私の夫とこんな風に取引なさるの！？やっぱりね！私はヤンに警告したのよ、 いつかこの女狐が男たちをたぶらかし始めるって！それで、あなたの手には何を持っているの？\n";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog1");
		break;
		
		case "helendrinking_joan_2":
			dialog.text = "な、な、なんですって！？この下郎め、よくもそんな口をきいたわね！？どこにも行かせないわよ、 うちの旦那がもうすぐ来るから、年長者への礼儀ってものを叩き込んでやるんだから！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JoanDialog3");
		break;
		
		case "helendrinking_fort_officer":
			dialog.text = "ここで何が起きているんだ？マッカーサー嬢！私は君のお父上をとても尊敬していたし、スヴェンソン旦那も我々 の友人だ……だが、前回どうなったか覚えていないのか？\nがっかりだ、士官の名にかけて、がっかりだぞ！誘ってくれてもよかったのに！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog");
		break;
		
		case "helendrinking_fort_officer_1":
			dialog.text = "ご親切にしていただき、マッカーサー嬢、ありがとうございます。\n皆、あなたが戻ってきてくれて本当に嬉しく思っております。\n何があったのかは大きな謎ですが、町で噂になっているのも無理はありません。\nそれでも、誰も詮索したりはしないとお約束いたします。\n最近、我々の船長の一人がご迷惑をおかけしたこと、心よりお詫び申し上げます。\nそして、特にあなたに感謝を伝えたいのです、ド・モール旦那。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog3");
		break;
		
		case "helendrinking_fort_officer_2":
			dialog.text = "すべてうまくいきますわ、お嬢様。デ・モール旦那、率直に申し上げますと――ドノヴァンがいかなる悪党・山賊のように振る舞おうと、艦隊が彼を公然と非難することは決してありません。むしろ、 彼を擁護する可能性のほうが高いでしょう。あなた方の小さな遠征は報告書に載り、 我が国とあなた方の国との関係を大いに複雑にしてしまいました。それでもなお、スヴェンソン旦那の影響力、 そしてキャップスターヴィルからあなたが受けた並外れた譲歩を考慮すれば、恐れることは何もありません。";
			link.l1 = "それは素晴らしいな。俺はそれに乾杯しようぜ！";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_FortDialog1");
		break;
		
		case "helendrinking_poorman":
			dialog.text = "失礼ですが、で、その仕事はどうなりましたか？";
			link.l1 = "「まだここにいるのか？」";
			link.l1.go = "helendrinking_poorman_1";
		break;
		
		case "helendrinking_poorman_1":
			dialog.text = "旦那、他にどこへ行けっていうんだ？ちょっと用を足しに行っただけなのに、あんたらの感傷的な話が聞こえてきて、 つい気分が熱くなっちまったんだ。感情的に、って意味だぜ！";
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.BoughtRainbow")) {
				link.l1 = "なんてこった！まあ、約束した以上、仕方ないな。行け、指揮を執れ。";
				link.l1.go = "helendrinking_poorman_bought";
			} else {
				link.l1 = "今はあなたに頼む仕事はありません、旦那。";
				link.l1.go = "helendrinking_poorman_notbought";
			}
		break;
		
		case "helendrinking_poorman_bought":
			dialog.text = "了解だぜ、船長！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helendrinking_poorman_notbought":
			dialog.text = "残念だな！まあ、とにかくごちそうさま、船長！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AddRainbow");
			AddDialogExitQuestFunction("HelenDrinking_LightsOut1NoArg");
		break;
		
		case "helensleep_amelia_mary":
			dialog.text = "イン・ノミネ・パトリス・エト・フィリイ・エト・スピリトゥス・サンクティ……入ってきなさい、息子よ。";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "こんにちは、アメリア母さん。あなたも僕に怒鳴るつもりですか？";
				link.l1.go = "helensleep_amelia_mary_know";
			} else {
				link.l1 = "消えろ！これは一体どんな悪夢だ？何が起きているんだ？俺は夢でも見ているのか？";
				link.l1.go = "helensleep_amelia_mary_notknow";
			}
		break;
		
		case "helensleep_amelia_mary_know":
			dialog.text = "いいえ、私の小さな鷹さん。でもヤンを許してあげて――あの人、つい興奮してしまったのよ。\nでもね、あなたを叱りたいのは本当なの。どうして教会に来たの？自分の罪を悔い改めに？それとも、 あの赤毛の子が目当てだったのかしら？";
			link.l1 = "自分でもわからない……";
			link.l1.go = "helensleep_amelia";
			link.l2 = "君も彼女を見たのか？俺の目を引いたんだ。";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_mary_notknow":
			dialog.text = "消えろ。もうとっくに会っているはずなのに、お前が全部を引き延ばしているんだ。\nなぜ教会に来た？自分の罪を悔い改めに来たのか？それとも、赤髪の奴が目当てだったのか？";
			link.l1 = "自分でもわからない……";
			link.l1.go = "helensleep_amelia";
			link.l2 = "君も彼女を見たか？俺の目を引いたんだ。";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen":
			dialog.text = "おはよう、私の鷹よ。まだ受付は始まっていないから、列に並んでお待ちください。";
			if (HelenSleep_TalkedToAmelia()) {
				link.l1 = "こんにちは、閣下。あなたも私に怒鳴るおつもりですか？";
				link.l1.go = "helensleep_amelia_helen_know";
			} else {
				link.l1 = "消えろ！これは一体どんな悪夢だ？何が起きているんだ？俺は夢でも見ているのか？";
				link.l1.go = "helensleep_amelia_helen_notknow";
			}
		break;
		
		case "helensleep_amelia_helen_know":
			dialog.text = "いいえ、私の鷹よ。それからヤンを許してやってくれ、あの男は気が立っていただけなんだ。\n君を叱る必要はないよ。君はちゃんとやった――赤毛のやつを教会まで追いかけたりしなかった。\nいい子だ！";
			link.l1 = "褒められるのは気分がいいな。特に、何のために褒められているのかはっきりしている時はなおさらだ。";
			link.l1.go = "helensleep_amelia";
			link.l2 = "君も彼女を見たのか？俺の目を引いたんだ。";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia_helen_notknow":
			dialog.text = "消えろ。もう会っているはずなのに、いつまで引き延ばしているんだ。こっちへ来い、褒めてやる――赤毛の女を教会まで追いかけなかったな。いい子だ！";
			link.l1 = "褒められるのは気分がいいな。特に、何のために褒められているのかはっきりしている時はなおさらだ。";
			link.l1.go = "helensleep_amelia";
			link.l2 = "君も彼女を見たか？俺の目を引いたんだ。";
			link.l2.go = "helensleep_amelia";
		break;
		
		case "helensleep_amelia":
			dialog.text = "細かいことは言わないわ、お馬鹿さん。でもこれだけは教えてあげる。あなたは偉大な人物になる運命なのよ。 多くの悪事も成すけれど、それ以上に善きことをもたらすわ。でも、幸福が約束されているわけじゃないの。 幸福というものはね、私の鷹さん、自分の道を歩み、決して迷わぬ者だけに与えられるものよ。そして、 誠実な女があなたが道を踏み外さぬよう助けてくれるわ。\nあなたには二人の女が現れる。そのどちらも幸福をもたらすけれど、金髪の方を選ばなければならないのよ。";
			link.l1 = "なぜそうなるんだ？自分のことは自分で決める！";
			link.l1.go = "helensleep_amelia_1";
		break;
		
		case "helensleep_amelia_1":
			dialog.text = "もちろん、自分で選べばいいが、金髪の方がいいぜ。そう決めたんだ。";
			link.l1 = "俺たちは何者だ？";
			link.l1.go = "helensleep_amelia_2";
		break;
		
		case "helensleep_amelia_2":
			dialog.text = "哀れな娘は自分の本当の名前すら知らない。\nその名を口にすれば、彼女はお前のものになる――そう言われているのさ。";
			link.l1 = "もう何もわからなくなった。";
			link.l1.go = "helensleep_amelia_3";
		break;
		
		case "helensleep_amelia_3":
			dialog.text = "ノックの音が聞こえるだろ？さっさと開けろ、間違えるんじゃねえぞ。";
			link.l1 = "確かに、誰かがノックしているな……入ってくれ！";
			link.l1.go = "exit";
			
			PlaySound("interface\knock.wav");
			
			AddDialogExitQuestFunction("HelenSleep_WakeUp");
		break;
		
		case "helendrinking_notifier":
			dialog.text = "旦那、スヴェンソンさんがあなたに少しお時間をいただきたいと申しております。";
			link.l1 = "くそっ、こりゃあ嫌な予感がするぜ。やってみるが、保証はできねえぞ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_End");
		break;
		
		case "islatesoro_pirate1":
			dialog.text = "運がいい日だな、お前ら！あいつがそのうちここに来るって言っただろ？\nさあ、お嬢ちゃん、武器を渡して俺たちと一緒に来てもらうぜ。";
			link.l1 = "違うぜ、野郎ども。あいつは俺と一緒だ。";
			link.l1.go = "islatesoro_pirate1_1";
		break;
		
		case "islatesoro_pirate1_1":
			dialog.text = "口出しするな、さもないと犬みたいに撃ち殺すぞ。あの娘にはいい金がかかってるんだ、 俺たちは腹を空かせた野郎どもで、道徳なんざ持っちゃいねえんだよ。";
			link.l1 = "そんな口の利き方を続けてみろ、二度と腹が減ることはなくしてやるぜ。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroSpawnSecond");
		break;
		
		case "islatesoro_pirate1_2":
			dialog.text = "ラッキー、お前、完全に気が狂ったのか？俺たちが先に彼女を見つけたんだぜ！ 俺に向かってそんな馬鹿なことをぬかす理由があるんだろうな！？";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog1");
		break;
		
		case "islatesoro_pirate1_3":
			dialog.text = "ここでネズミなのはお前だ！でっかいスペイン野郎をぶっ潰したばかりだぜ、これで一年はのんびりできるってもんよ！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog3");
		break;
		
		case "islatesoro_pirate2":
			dialog.text = "おやおや、誰が来たかと思えば。よし、他の奴らは出ていけ。そこの奥さん、あんたは俺たちと来てもらうぜ。\n";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog");
		break;
		
		case "islatesoro_pirate2_1":
			dialog.text = "俺たちの方が数も多いし、腕っぷしも強いんだぜ、デーン。他に理由がいるのかよ、このドブネズミめ？\nお前がまともな獲物を手に入れてからもう半年も経ってるし、ヴアジーの食卓のパンくずを拾って食ってるじゃねえか！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog2");
		break;
		
		case "islatesoro_pirate2_2":
			dialog.text = "";
			link.l1 = "ここでは平和的な解決は望めそうにないな。";
			link.l1.go = "islatesoro_pirate_a";
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedB")) {
				link.l2 = "何だと？ラッキーだと？奴とヴアジエが組んでお前にインチキな情報を流したって噂を聞いたぜ。 だからお前の海での不運続きも納得だな。";
				link.l2.go = "islatesoro_pirate_b";
			}
			bOk = (!CheckAttribute(pchar, "questTemp.Mtraxx.Retribution.Choice")) || (pchar.questTemp.Mtraxx.Retribution.Choice == "bad");
			if (!CheckAttribute(pchar, "questTemp.HelenDrinking.IslaTesoroAmbush.TriedC") && CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold") && bOk) {
				link.l3 = "こんな茶番にはもううんざりだ。イスラ・テソロ、俺の声を聞け！カルタヘナで俺と一緒だったのは誰だ！？ メリダを俺と一緒に焼き払ったのは誰だ！？このネズミどもがチャーリー・プリンス本人に歯向かうつもりか！ 見せてやろうぜ、野郎ども！\n";
				link.l3.go = "islatesoro_pirate_c";
			}
		break;
		
		case "islatesoro_pirate_a":
			dialog.text = "まだここにいるのか、クラゲ野郎？よし、野郎ども、行くぞ。船長を縛り上げろ、女の方は後で片付けるからな、 わかったか？\n";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroPirateDialog4");
		break;
		
		case "islatesoro_pirate_a_1":
			dialog.text = "ああ、せめて血の一滴でも流そうぜ。へへっ。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_IslaTesoroA");
		break;
		
		case "islatesoro_pirate_b":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedB = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 60) {
				dialog.text = "「なんだと！？くそっ、やっぱりあのメガネ野郎とグルだったか！野郎ども、全員ぶった斬れ！女の子は後で回収するぞ！ 」";
				link.l1 = "";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroB");
			} else {
				dialog.text = "何をぺちゃくちゃ言ってやがる、船長？まともな連中が商談してるんだ、さっさと失せろ。";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "islatesoro_pirate_c":
			pchar.questTemp.HelenDrinking.IslaTesoroAmbush.TriedC = true;
		
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 50) {
				DialogExit();
				AddDialogExitQuestFunction("HelenDrinking_IslaTesoroC");
			} else {
				dialog.text = "何をぺちゃくちゃ言ってやがる、船長？俺はチャーリー・プリンスを見たことがあるが、 お前なんか奴の足元にも及ばねえ。まともな連中が商談してる間に、とっとと失せな。";
				link.l1 = "";
				link.l1.go = "islatesoro_pirate2_2";
			}
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "francois":
			dialog.text = "シャルル・ド・モール？アンリ・ド・モンペの息子か？";
			link.l1 = "その通りです、旦那。で、あなたは誰ですか？";
			link.l1.go = "francois_1";
		break;
		
		case "francois_1":
			dialog.text = "フランソワ・ド・タヴァンヌ大佐。これは直接の挑戦と受け取ってもらおう、旦那。決闘の手袋は投げられた。 貴様ごときで手を汚す気もないが、誓ってやる、俺の剣がお前の血を味わうことになるぞ！";
			link.l1 = "決闘だと？それなら、もっと本気を出してもらわないとな、カーネル。今のお前じゃ、ただの野盗と間違われるだけだぜ、 この辺りじゃそんな連中とは話も短いんだ！どういうつもりか説明しろ！";
			link.l1.go = "francois_2";
		break;
		
		case "francois_2":
			dialog.text = "「俺が国王と祖国のために血を流していた間に、旦那！お前は……お前は俺の妻を誘惑して楽しんでいたんだな！」";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog");
		break;
		
		case "francois_3":
			dialog.text = "黙りなさい、奥様。その大胆な服装はどんな女性の名誉も汚すものですわ、もっとも、 この卑しい貴婦人たらしの隣にはよくお似合いですけれど！";
			link.l1 = "決闘するにはまだ理由が足りませんな、大佐。ついでに申し上げますが、 あなたもここで同じくらい品位に欠けた振る舞いをなさっていますよ。";
			link.l1.go = "francois_4";
		break;
		
		case "francois_4":
			dialog.text = "それでは不十分ですか？私は調べました――今や私の立場には十人もの高貴な旦那が座っていてもおかしくありません、旦那。しかし、詳細をお望みなら、 恥を忍んで告白しますが、あなたの情熱の一つはルル・ド・タヴァン、最も美しく誠実な女性だったのです！";
			link.l1 = "ルルか……それで、彼女はどうしてるんだ？";
			link.l1.go = "francois_5";
		break;
		
		case "francois_5":
			dialog.text = "黙れ！お前が与えた苦しみに耐えきれず、私の妻は最近亡くなったのだ！私はお前を探すために、 ほぼ一年と莫大な金を費やしたぞ、この悪党め！もう言葉はいらん！決闘を受けろ、さもなくば犬のように殺してやる。 リチャード！証人になってくれ！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog2");
		break;
		
		case "francois_6":
			dialog.text = "黙れ、旦那！挑戦を受けるか、残っているかもしれない名誉のかけらまで失うか、どちらかだ！";
			if (pchar.HeroParam.HeroType == "HeroType_1") {
				link.l1 = "決闘は決闘だ。正直に言うと、こういうのは好きなんだよな。\n船長、そろそろ大佐に「立派な棺桶を用意するように」と伝えてくれ。";
			} else {
				link.l1 = "喧嘩がしたいのか？望みどおりにしてやる！\n船長、そろそろ大佐に「立派な棺を用意するように」と伝えてくれ。";
			}
			link.l1.go = "francois_duel";
			link.l2 = "ここはヨーロッパじゃありませんよ、大佐。カリブでの名誉は得るのが難しいですが、失うのもそう簡単じゃありません。 私が決闘を断るのは、ただ望んでいないからです。";
			link.l2.go = "francois_refuse";
		break;
		
		case "francois_7":
			dialog.text = "お前の父親はもう墓場まであと一歩だ、このクズ野郎！そして俺が必ずお前の臆病ぶりをあいつに知らせてやるぜ！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog7");
		break;
		
		case "richard":
			dialog.text = "大佐、あなたの決闘の権利は認めますが、単なる野盗行為は許しません！\nド・モール旦那、私はリチャード・スモール船長です。タヴァンヌ大佐に名誉を賭けて応じる覚悟はありますか？";
			link.l1 = "少々お待ちを、船長。ルルのことはよく知っていました……あの娘はしょっちゅう男を変える癖がありましたし、私よりもずっと健康だった……彼女はどうやって亡くなったんです、カーネル？あなたが帰国する前ですか、それとも後ですか？";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog3");
		break;
		
		case "richard_1":
			dialog.text = "どうぞ、フランソワ、私に任せてください。\nド・モール旦那、あなたは決闘を申し込まれました。\nブルーヴェルド士官協会は、タヴァンヌ大佐の名誉回復の要求が正当であると認めています。\n挑戦を受けるか、名誉を失うか、どちらかです。";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog5");
		break;
		
		case "richard_2":
			dialog.text = "シャルル、お願いですわ、ここは紳士の集まりですのよ。そんなのは相応しくありませんわ。大佐はあなたに会うために、 はるばるいらしたのです！これは大変な不祥事ですわ！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog8");
		break;
		
		case "richard_3":
			dialog.text = "は、はい、もちろんです、お嬢様。でも私は……";
			link.l1 = "";
			link.l1.go = "exit";
			CharacterTurnToLoc(npchar, "quest", "helen");
			
			AddDialogExitQuestFunction("HelenDrinking_AfterFrancoisDeath1");
		break;
		
		case "richard_4":
			dialog.text = "ド・モール船長、今日はあなたの日ですぞ！あまり正々堂々とした戦いではありませんでしたが、 本日あなたは名誉を守りました。";
			link.l1 = "何かおっしゃいましたか、船長？今日の予定にもう一戦ぐらいならねじ込めそうですわ。";
			link.l1.go = "richard_5";
		break;
		
		case "richard_5":
			dialog.text = "申し訳ありません、船長。ちょっと緊張してしまって！";
			link.l1 = "ここにあなたがいる必要はもうないと思う。";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_DuelVictory");
		break;
		
		case "richard_duel":
			dialog.text = "「公平な決定だ！たとえあまり威厳のある言い方じゃなかったとしても……\n諸君！始めよう！」";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuel");
		break;
		
		case "alonso":
			dialog.text = "船長、あの偉そうな連中が使う難しい言葉は全部わかるわけじゃねえが、 臆病者呼ばわりされたやつをそのままにしとくのは普通じゃねえぜ。ぶん殴ってやれよ、船長。そうしねえと、 俺たちの船員が不安になるぜ。";
			link.l1 = "血が欲しいのか？人生が退屈で刺激が足りねえのか？血ならくれてやるぜ、この野郎ども！";
			link.l1.go = "francois_duel";
			link.l2 = "うわーん、怖いよぉ。もう終わりですか、旦那方？俺には行くところがあるんでね。";
			link.l2.go = "alonso_refuse";
		break;
		
		case "alonso_1":
			dialog.text = "うちの船長が公の挑戦から逃げたら、見栄えが悪いぜ。あの貴族をぶっ飛ばしてやれよ、剣の腕は知ってるんだからな！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog9");
		break;
		
		case "alonso_refuse":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog6");
		break;
		
		case "francois_refuse":
			dialog.text = "腰抜けめ！女たらし！クズ野郎！怖じ気づいたか、この悪党が？みんな、今の見たか！？リシャール、 どうせ俺があいつを殺してやる！";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_AmbushDialog4");
		break;
		
		case "francois_duel":
			DialogExit();
			
			AddDialogExitQuestFunction("HelenDrinking_SetupDuelDialog");
		break;
		
		case "francois_sit":
			dialog.text = "お、お前なんて奴だ！大丈夫だ、怪我には慣れてる。すぐ回復するし、そして……";
			link.l1 = "脅しのように聞こえるな、大佐。俺は脅しが大嫌いなんだぜ。";
			link.l1.go = "francois_sit_kill";
			link.l2 = "回復したら、自分の負傷の経緯を士官仲間に自慢するのを忘れるなよ。";
			link.l2.go = "francois_sit_taunt";
		break;
		
		case "francois_sit_kill":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) - 1;
			Notification_Approve(false, "Helena");
			
			AddDialogExitQuestFunction("HelenDrinking_FinishFrancois");
		break;
		
		case "francois_sit_taunt":
			DialogExit();
			
			pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
			Notification_Approve(true, "Helena");
			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP, 300);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 300);
			
			AddDialogExitQuestFunction("HelenDrinking_SpareFrancois");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}

bool HelenSleep_TalkedToAmelia() {
	if (GetCharacterIndex("Amelia") < 0) {
		return false;
	}
	
	sld = CharacterFromID("Amelia");
	if (sld.dialog.currentnode == "amelia") {
		return false;
	}
	
	return true;
}
