// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Konuş, dinliyorum";
			link.l1 = "Yanılmışım. Hoşça kal.";
			link.l1.go = "Exit";
			//Цена чахотки
			if (!CheckAttribute(npchar, "quest.Consumption") && CheckAttribute(pchar, "questTemp.Consumption") && pchar.questTemp.Consumption == "begin")
			{
				link.l1 = "Burada bir salgın olduğunu duydum, doğru mu?";
				link.l1.go = "Consumption";
			}
		break;
		
		//--> Цена чахотки
		case "Consumption":
			dialog.text = "Doğru söylüyorsunuz, bu yüzden geçerli bir sebebiniz yoksa zindanlara gitmekten kaçının. Neden bununla ilgileniyorsunuz?";
			link.l1 = "Sadece merakımdan soruyorum. Yani adamlarım fazla içip, fazla gürültü yaparsa ve sonunda buraya düşerse, o zaman sarı keten hazırlamam mı gerekecek?";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "Ne yazık ki, señor, şaka yaptıysanız bile ben anlayamadım. Zindanlar nemli ve soğuk, malumunuz buranın iklimi böyle. Verem bu zindanların sık sık misafiri olur. Adamlarıma yiyecek taşımaları için fazladan para vermek zorunda kalıyorum. Orada devriye gezmek, neredeyse kürek mahkûmluğu kadar kötü sayılır.";
			link.l1 = "Üzgünüm, sadece bunun ne kadar ciddi olduğunu öğrenmek istemiştim?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Far too serious. We don't even have a physician here; he died of the damn consumption too. Now only a medic from the local garrison examines prisoners once a week. But who cares about these tramps and criminals?\nMost folks think they fully deserved such a fate, and it's hard to argue with that.";
			link.l1 = "Tıptan çok anlamam, ama bildiğim kadarıyla verem tehlikeli ve ölümcüldür; fakat burada olduğu gibi insanları birkaç gün içinde öldürmez. Kurbanlar aylarca, hatta yıllarca acı çekmez mi normalde?";
			link.l1.go = "Consumption_3";
		break;
		
		case "Consumption_3":
			dialog.text = "Az önce de belirttiğiniz gibi, siz bir hekim değilsiniz, dolayısıyla hastalığın özelliklerinden bahsetmeniz sadece... uydurma bir yalan olabilir. Ben sadece, hastalık onu da almadan önce doktorumuzun söylediklerini tekrarladım. O yüzden merakınızı ve alaycı tavrınızı anlamıyorum. Burada insanlar ölüyor!";
			link.l1 = "Az önce bunu hak ettiklerini söylemedin mi?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Yeter, señor! Sanırım seninle benim zeka yarışından daha önemli işlerimiz var. Kapı tam arkanızda.";
			link.l1 = "Pekala, nezaketim için bağışlayın, zaten gidiyorum.";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			DialogExit();
			npchar.quest.Consumption = "true";
			pchar.questTemp.Consumption.Commandant = "true";
			AddQuestRecord("Consumption", "3");
			pchar.quest.Consumption.win_condition.l1 = "location";
			pchar.quest.Consumption.win_condition.l1.location = "PortSpein_houseF2";
			pchar.quest.Consumption.function = "Consumption_CommandantHouse";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
