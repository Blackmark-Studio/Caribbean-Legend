// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあれば言え。","お聞きしましょう、ご質問は何でしょうか？"),"これは二度目のご質問でございますね……","これで三度目のご質問でございますが……","いつまで続くのですか！？私は植民地の案件で多忙な身ですのに、あなたはまだ私を煩わせるのですか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えました、申し訳ありません。","今は駄目だ。場所も時も間違っている。"),"確かに、今は申し上げることがございません、申し訳ありません。","後でお尋ねします。","申し訳ありません、 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
			{
				link.l1 = "旦那知事、恐ろしい知らせがございます。手短に申し上げますと、奥様があなたを裏切ろうとしております。奥様は私に、 あなたの書斎の金庫の鍵を開けるよう頼んできました。このことをお伝えすべきだと思いました。";
                link.l1.go = "FMQT";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+"、旦那。私は総督シュヴァリエ・ド・ポワンシーの命により参上いたしました。私の任務は、 本国から植民地視察の命を受けて到着したノエル・フォルジェという名の男爵をトルトゥーガまでお連れすることです。 彼の主な目的はフランス西インド交易会社の設立でございます。彼をご紹介いたします……詳細はご本人よりご説明いたします。";
                link.l1.go = "patria_tortuga";
			}
		break;
		
		case "FMQT":
			dialog.text = "な、なんだと？またか？あの女め！絶対に後悔させてやる、誓ってもいい！カンパチョがあの女を泣かせてやるぜ。 まだここにいるのか？さっさと失せろ！";
			link.l1 = "「私は思いました……」";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
			else link.l1.go = "FMQT_1";
		break;
		
		case "FMQT_1":
			Notification_Skill(false, 26, SKILL_LEADERSHIP);
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "いつも同じだな！ほら、これを持っていけ！これが机の上にある全てだ！さあ、出ていけ！";
			link.l1 = "ありがとうございます、閣下。では、これにて失礼いたします。";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_2":
			AddMoneyToCharacter(pchar, 1000);
			GiveItem2Character(pchar, "pistol6");
			GiveItem2Character(pchar, "purse1");
			Log_Info("You have received a double barreled pistol and a purse of doubloons");
			dialog.text = "いつも同じだな！ほら、これを持っていけ！これが机の上にある全てだ！…まあ、いいだろう、お前はこの島にあふれている愚か者や負け犬どもとは違うようだな。少し余分にやる…さあ、もう出ていけ！";
			link.l1 = "ありがとうございます、閣下。では、これにて失礼いたします。";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_3":
			DialogExit();
			pchar.quest.FMQT_late1.over = "yes";
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.FMQT = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Tortuga", "7");
			CloseQuestHeader("FMQ_Tortuga");
			FMQT_ClearChest();
		break;
		
		// Jason НСО
		case "patria_tortuga":
			dialog.text = "よろしいです、シャルル・ド・モール船長。男爵には然るべき待遇を用意し、 私もできる限り彼の任務を支援いたしましょう。";
			link.l1 = "";
			link.l1.go = "patria_tortuga_1";
		break;
		
		case "patria_tortuga_1":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
