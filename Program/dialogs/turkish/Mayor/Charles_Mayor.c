// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Ne istiyorsunuz? Sorunuzu sorun.","Dinliyorum, sorunuz nedir?"),"Bu, ikinci kez sormaya çalışıyorsunuz...","Bu üçüncü kez tekrar sormaya çalışıyorsunuz...","Bu ne zaman bitecek?! Ben meşgul bir adamım, koloninin işleriyle uğraşıyorum, sen ise hâlâ bir şeyler sormaya çalışıyorsun!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Fikrimi değiştirdim...","Şimdi değil. Yeri ve zamanı değil."),"Doğru... Ama sonra, şimdi değil...","Soracağım... Ama birazdan...","Üzgünüm, "+GetAddress_FormToNPC(NPChar)+"...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "saga" && !CheckAttribute(npchar, "quest.saga"))
			{
				link.l1 = "Chevalier de Poincy ile görüşmek istiyorum. Bu, kardeşimin borcuyla ilgili.";
                link.l1.go = "puancie";
			}
			//<-- Бремя гасконца
		break;
		
		case "puancie":
			dialog.text = "Aha, evet, o borcun farkındayım... Gerekli miktar yanınızda mı?";
			if (sti(pchar.money) >= 1000000)
			{
				link.l1 = "Elbette ettim. Başka türlü nasıl olabilirdi ki?";
				link.l1.go = "puancie_1";
			}
			else
			{
				link.l1 = "Hayır, henüz o kadar param yok.";
				link.l1.go = "puancie_exit";
			}
		break;
		
		case "puancie_exit":
			dialog.text = "O halde onu bulduğunda geri gel, Şövalye'yi rahatsız etme.";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "puancie_1":
			dialog.text = "Sağdaki kapıdan geçin o zaman. Şövalye sizi kabul edecek.";
			link.l1 = "Teşekkürler!";
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
