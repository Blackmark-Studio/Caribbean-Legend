// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあればどうぞ。","お話を伺いましょう、ご質問は何でしょうか？"),"これで二度目のご質問でございますね…","これで三度目のご質問でございます…","いつまで続くのですか！？私は植民地の案件で忙しい身なのに、あなたはまだ私を煩わせるのですか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考え直しました……","今は駄目だ。場所も時も間違っている。"),"「確かに……しかし、今ではなく後で……」","聞いてみよう……だが、少し後でな……","申し訳ありません。 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "閣下、この島で違法な取引活動が行われていることをご報告申し上げます。";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "絹製帆布の密輸に関する任務の報告を伺いたい。";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "私はフィリップ・ド・ポワンシー総督代理として参りました。私の任務は、 オランダ人から捕らえた奴隷を引き渡すことですが、間違いありませんか？";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "約束通り、奴隷たちを連れてまいりました。";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "私はフィリップ・ド・ポワンシー総督の指示で、 オランダ人に対するキュラソーへの共同遠征に参加するために到着いたしました。";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "私の戦隊は減りましたので、今出発できます。";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "興味深いですね。お話を伺いましょう。";
			link.l1 = "確かな筋からの情報によれば、イギリスの旗を掲げたオランダのブリガンティン船『ユトレヒト』が、 ポートランド湾で大量の絹製帆布を長い間荷下ろししているとのことです。\n彼らはすでに一年以上、毎月10日から15日の夜間に活動しているのです。";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "「あなたの情報源は本当に信頼できるのですか？」";
			link.l1 = "時には自分自身さえも信じられないことがありますが、この情報を明かした男は信頼できる人物でございます。\nそれに、彼が嘘をつく理由もございませんでした。";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
            dialog.text = "承知しました、船長。これは重大な案件でございますので、たとえあなたの密告者が虚偽を述べていたり、 単なる誤解であったとしても、提示された情報に基づき行動せねばなりません。 ご指定の時刻に沿岸警備隊を派遣いたします。そして、もしあなたの情報が確認されれば、 寛大な報酬をお約束いたします。このような違法行為は厳しく取り締まらねばなりません。";
			link.l1 = "お目にかかります "+sTemp+" 16日には状況もきっと解決していることでしょう。";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = sti(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
			DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "this";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "next";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
			if (CharacterIsAlive("Mtr_Utreht"))
			{
				sld = CharacterFromID("Mtr_Utreht");
				sld.lifeday = 0;
			}
		break;
		
		case "Mtraxx_4":
            dialog.text = "あなたの情報は正しかったようです、船長。我々は取引の最中に犯罪者たちを待ち伏せしました。「ユトレヒト号」 は逃走を試み、反撃もしましたが、我々の哨戒コルベット艦によって撃沈されました。買い手のうち四名が逮捕に抵抗し、 一人は射殺され、残り三人はジャングルに逃げ込みました。絹80反の全積荷はポートロイヤルの財務庫に移されました。この組織の首謀者を特定することはできず、死亡者も身元不明で、 他の者も逃亡しましたが、この作戦は完全な成功であると宣言いたします。 これらの悪党どもが再びここに戻ることは二度とないでしょう。\n船長、あなたが勤勉にして詐欺師たちを暴いてくれたことで、我々は大いに助かりました。これが報酬の1万ペソです。";
			link.l1 = "ご恩義に感謝いたします、閣下。すべてが計画通りに進み、密輸業者たちが然るべき報いを受けたこと、 私も嬉しく思います。\nそれでは、これにて失礼いたします。どうぞ良い一日をお過ごしください。";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "まさにその通りです。何人の奴隷を連れてきましたか？";
				link.l1 = "まだ作業中でございます。すぐに結果を持って戻ってまいります。";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "まさにその通りです。何人の奴隷を連れてきましたか？";
			link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "ふむ、シュヴァリエは奴隷が三千人以上いると約束したのだが";
			link.l1 = "その通りです。これは私の責任でございます――奴隷の一部は敵船の砲撃で命を落とし、また一部は道中で死にました。私の過ちを正し、必ずお戻しいたします。 すべて契約通りに執り行います。";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "素晴らしい！ポワンシー騎士とは本当に取引ができますな。総督閣下に、 キュラソー攻撃のための私の艦隊が一か月後には準備できるとお伝えください。 きっとこの遠征のためにあなたを私のもとへ派遣なさるでしょうから、近いうちにまたお会いできますな、 ド・モール旦那。";
			link.l1 = "またお会いできれば嬉しく存じます、大佐。\nそれでは、これにてご無礼いたします。";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры д'Ойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "あなたが来ると疑いませんでした。さらに素晴らしい！我々の戦隊は準備万端です。一等戦列艦と四等艦が二隻。 全戦隊の最大隻数は五隻を超えてはなりません。";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "それでは余分な船は埠頭に残し、二隻だけ残します。\n最終的に五隻の船となります。";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "はい、まさに五つ、これ以上はありません。出発しましょう。";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "完璧です。では、これから我々が行動する計画を説明いたします：もし何か変更や追加したいことがあれば、 そのときにご相談いたしましょう。";
			link.l1 = "「お伺いします、Colonel。」";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "キュラソーを占領しても意味はありません。あそこは諸島におけるオランダの主要な植民地であり、 たとえウィレムスタッドの要塞で彼らの旗を奪い、イギリスやフランスの旗を掲げたとしても、 その島を維持するのは非常に困難でしょう。オランダ側は奪還のためにあらゆる手段を講じ、 軍艦隊を差し向けてくるはずです。\nそもそも占領は義務ではないので、意味がありません。それよりも重要なのは、スタイフェサントに我々 に有利な条件で条約に署名させることです。そのためには敵の主力防衛を壊滅させ、 ウィレムスタッド植民地の完全破壊という脅威をオランダ側に与えるだけで十分でしょう。";
			link.l1 = "その条約は何についてのものでございますか？";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "この条約は私とシュヴァリエ・ド・ポワンシーによって作成されました。\n内容は貿易の諸側面、会社とイングランド間の「貿易戦争」の終結、 スタイフェサントによるシント・マールテン島への要求の否認、 そしてあなたにはあまり関係のないその他の政治的事項についてです。";
			link.l1 = "承知いたしました。";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "作戦はこうだ。まず、我々の全戦力をもって砦を攻撃し、破壊する。オランダ人は上陸部隊を予想するだろうが、我々 はそれを行わない。海から要塞を強襲する際に最も多くの犠牲が出るものだ。代わりに、島の二か所――サンタ・マリア岬とブランカ潟――に強襲部隊を上陸させ、陸路でウィレムスタッドの城門へ進軍する。\n私は野戦砲を船で運ぶよう命じてある。キュラソーには不通の密林はなく、大砲を容易に陸上で運ぶことができる。 オランダ人が事態を把握できず困惑している間に、我々は密林から町を狙い、砦から陸路での増援を完全に遮断する。 その後、町を大砲で砲撃する。\nもちろん、砦の守備隊は必ずや打って出るだろうが、野戦砲と我々の銃兵の前には無力だ。 たとえ砦の大砲が使える状態でも、密林に持ち込むことはできまい。さらに、我々の艦隊は海上からの上陸準備を装い、 敵に恐怖を与え士気を削ぐ。しばらくしてオランダ人が状況の絶望を完全に悟った時、我々 は彼らの使節を呼び交渉に臨む。\nどう思うかね、船長？";
			link.l1 = "素晴らしい作戦だ！しかも一番良いのは、砦の壁際で兵士を一人も失わずに済むことだ。";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "私の考えをお気に召していただけて嬉しいです。それでは、先へ進みましょう！";
			link.l1 = "行こう！";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
