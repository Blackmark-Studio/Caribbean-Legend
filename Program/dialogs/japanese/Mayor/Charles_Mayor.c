// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("何の用だ？聞きたいことがあればどうぞ。","お聞きしましょう、ご質問は何ですか？"),"二度目のご質問でございますね…","あなたが再び尋ねようとするのはこれで三度目です…","いつになったら終わるのだ？！私は忙しい身であり、植民地の事務に追われているのだぞ。それなのに、 まだ何か聞こうとしているのか！","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを改めました……","今は駄目だ。場所も時も間違っている。"),"確かに……だが、今ではなく、後で……","聞いてみます……でも、少し後で……","申し訳ございません、 "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
			{
				link.l1 = "シュヴァリエ・ド・ポワンシーにお目にかかりたいのです。兄の借金についてお話があります。";
                link.l1.go = "puancie";
			}
			//<-- Бремя гасконца
		break;
		
		case "puancie":
			dialog.text = "ああ、そう、その借金のことは承知している……必要な金額はお持ちですか？";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "もちろんでございます。他にどうなり得ましょうか？";
				link.l1.go = "puancie_1";
			}
			else
			{
				link.l1 = "いいえ、まだそんなに多くのお金は持っておりません。";
				link.l1.go = "puancie_exit";
			}
		break;
		
		case "puancie_exit":
			dialog.text = "それなら、それを手に入れてから戻ってきなさい。そしてシュヴァリエを煩わせないでください。";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "puancie_1":
			dialog.text = "それでは、右側の扉からお入りください。シュヴァリエがお迎えいたします。";
			link.l1 = "ありがとうございます！";
			link.l1.go = "puancie_2";
		break;
		
		case "puancie_2":
			DialogExit();
			npchar.quest.saga = "true";
			bDisableFastReload = true;//закрыть переход
			LocatorReloadEnterDisable("Charles_townhall", "reload1_back", true);//чтобы не вышел
			LocatorReloadEnterDisable("Charles_townhall", "reload3", false);//откроем вход к Пуанси
			ref sld = characterFromId("Puancie");
			ChangeCharacterAddressGroup(sld, "Charles_Roomtownhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			sld.dialog.currentnode = "saga";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
