// диалог начальника шахты
void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		location = &Locations[FindLocation(pchar.location)];
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("Burada yüzünü göstermeye cüret mi ediyorsun?! Cesur musun yoksa sadece aptal mı, bilmiyorum...","Bu tembeller düşmanın evime girmesine nasıl izin verdi? Bunu aklım almıyor...","Demek ki, burada böyle alçaklar dolaşabiliyorsa, muhafızlarım bir bakır para bile etmiyor..."),LinkRandPhrase("Ne istiyorsun?"+GetSexPhrase("serseri","pislik")+"?! Askerlerim zaten peşindeler, "+GetSexPhrase(", pis kirli korsan","")+"!","Pis katil, hemen evimden defol! Muhafızlar!","Senden korkmuyorum, "+GetSexPhrase("fare","orospu")+"! Yakında kalemizde asılacaksın, ondan sonra da fazla uzağa gidemezsin..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("Bu askerler tek bir peso bile etmez...","Beni asla yakalayamayacaklar."),RandPhraseSimple("Kapa çeneni, "+GetWorkTypeOfMan(npchar,"")+", ya o pis dili kökünden sökerim!","Sana tavsiyem, sessizce otur; belki de sağ çıkarsın..."));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
    			dialog.text = "Madende düşman var! Alarm!";
				link.l1 = "Aaah, şeytan!";
				link.l1.go = "fight"; 
				break;
			}	
			dialog.text = LinkRandPhrase(""+TimeGreeting()+", señor. Ben "+GetFullName(npchar)+", Los-Teques madenindeki maden mühendisi. Sizi buraya getiren nedir?","Merhaba, señor. Ne istemiştiniz?","Hmm... benden bir şey mi istediniz, señor? Dinliyorum.");
			if (!CheckAttribute(location, "quest.info"))
			{
				link.l9 = "Buraya yeni geldim ve bu maden hakkında daha fazla bilgi almak istiyorum...";
				link.l9.go = "info";
			}
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 4)
			{
				link.l2 = "Ambarımda ilginizi çekebilecek bir yük var. Madende çalıştırmak için köleler, tam olarak. Pazarlık yapmak ister misiniz?";
				if (!CheckAttribute(location, "quest.slaves")) link.l2.go = "slaves_0";
				else link.l2.go = "slaves";
			}
			link.l1 = "Sadece merhaba demek için geldim, şimdi de hemen gidiyorum.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "info":
			dialog.text = "Los-Teques mine extracts gold for the Spanish Crown. Everything we extract belongs to Spain. Here, we find not only gold, but also silver nuggets and valuable precious stones. We don't sell gold here; everything we extract is delivered to the Old World under a reinforced convoy. But we have two exceptions for gold and silver nuggets. First, you can buy a certain amount of them in our local store from the quartermaster. Sometimes salaries don't arrive on time, so we have to keep some coin savings here for such cases; that is why local trading is allowed. Second, we are constantly in need of manpower, so we exchange nuggets for slaves. Therefore, talk to me if you have something to offer, and we will do business. I believe the rules of conduct in the mine are obvious: don't steal, don't distract the convicts, and don't bother the soldiers, otherwise you won't like the consequences.";
			link.l1 = "İyiyim, teşekkürler!";			
			link.l1.go = "exit";
			location.quest.info = "true";
		break;
		
		// генератор купли-продажи рабов
		case "slaves_0":
			location.quest.slaves.qty = 200; // стартовая потребность
			dialog.text = "Elbette, señor! Kaç tane var?";
			link.l1 = "Sahip oldum "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
			link.l1.go = "slaves_1";
		break;
		
		case "slaves":
			location.quest.slaves.qty = sti(location.quest.slaves.qty)+GetNpcQuestPastDayParam(location, "slave_date"); // каждый день даёт +1 потребности
			if (sti(location.quest.slaves.qty) > 350) location.quest.slaves.qty = 350; // максимум потребности
			if (sti(location.quest.slaves.qty) < 5)
			{
				dialog.text = "Señor, maalesef şu anda daha fazla köleye ihtiyacımız yok. Ama durum her an değişebilir, bu yüzden birkaç hafta sonra ya da başka bir zaman tekrar uğrayın.";
				link.l1 = "Pekâlâ, señor, anladım. Şimdi onlara ihtiyacınız yok, ama bir gün gerekebilirler.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Elbette, señor! Kaç tane var?";
				link.l1 = "Sahip oldum "+FindRussianQtyString(GetSquadronGoods(pchar,GOOD_SLAVES))+".";
				link.l1.go = "slaves_1";
			}
		break;
		
		case "slaves_1":
			dialog.text = "Her bir köle için sana ya bir altın külçe ya da iki gümüş külçe ödemeye hazırım. Hangisini seçiyorsun?";
			link.l1 = "Altın külçeleri.";
			link.l1.go = "slaves_g";
			link.l2 = "Gümüş külçeleri.";
			link.l2.go = "slaves_s";
			link.l3 = "Üzgünüm, señor, ama fikrimi değiştirdim. Başka bir zaman.";
			link.l3.go = "slaves_exit";
		break;
		
		case "slaves_g":
			location.quest.slaves.type = "gold";
			dialog.text = "Pekâlâ. Bana kaç köle satacaksın?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_s":
			location.quest.slaves.type = "silver";
			dialog.text = "Peki. Bana kaç köle satacaksın?";
			link.l1 = "";
			link.l1.edit = 6;
			link.l1.go = "slaves_trade";
		break;
		
		case "slaves_trade":
			iTotalTemp = sti(dialogEditStrings[6]);
			if (iTotalTemp < 1)
			{
				dialog.text = "Señor, saçma şakalara ayıracak vaktim yok. Eğer şaka yapmak istiyorsan, meyhaneye git!";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > GetSquadronGoods(pchar, GOOD_SLAVES))
			{
				dialog.text = "Señor, bence biraz dinlenmeniz gerek. Belki de çok yoruldunuz ya da güneş çarpması geçirdiniz. Meyhaneye gidin, biraz dinlenin, sonra pazarlığımıza devam edebiliriz.";
				link.l1 = "Hmm...";
				link.l1.go = "slaves_exit";
				break;
			}
			if (iTotalTemp > sti(location.quest.slaves.qty))
			{
				dialog.text = "Maalesef, señor, şu anda o kadar çok köleye ihtiyacımız yok. Şu an için madenin ihtiyacı olan sayı "+FindRussianQtyString(sti(location.quest.slaves.qty))+" . Bu kadarını satacak mısın?";
				link.l1 = "Evet, tabii ki!";
				link.l1.go = "slaves_max";
				link.l2 = "Hmm... Sanırım değilim.";
				link.l2.go = "slaves_exit";
				break;
			}
			dialog.text = ""+FindRussianQtyString(iTotalTemp)+"? Mükemmel. Lütfen onları kasaba kapılarına getirmeleri için emir verin. Adamlarımı onları almaya göndereceğim.";
			link.l1 = "Endişelenmeyin, señor. Köleleriniz zamanında size teslim edilecek. Gerekli tüm talimatları hemen vereceğim.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_max":
			iTotalTemp = sti(location.quest.slaves.qty);
			dialog.text = "Mükemmel. Lütfen onları kasaba kapılarına getirmelerini emredin. Adamlarımı onları almaya göndereceğim.";
			link.l1 = "Endişelenmeyin, señor. Köleleriniz zamanında size teslim edilecek. Gerekli tüm emirleri hemen vereceğim.";
			link.l1.go = "slaves_calk";
		break;
		
		case "slaves_calk":
			DialogExit();
			Log_Info("Exchange of slaves for ingots has been completed");
			PlaySound("interface\important_item.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,5,10);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, iTotalTemp);
			if (location.quest.slaves.type == "gold") TakeNItems(pchar, "jewelry5", iTotalTemp);
			else TakeNItems(pchar, "jewelry6", iTotalTemp*2);
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
			location.quest.slaves.qty = sti(location.quest.slaves.qty)-iTotalTemp;
		break;
		
		case "slaves_exit":
			DialogExit();
			DeleteAttribute(location, "slave_date");
			SaveCurrentNpcQuestDateParam(location, "slave_date");
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		    LAi_group_Attack(NPChar, Pchar);
			i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
			if (i != -1)
			{
			    LAi_group_Attack(&Characters[i], Pchar);
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
