#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
    int iTest, iTemp;
	string sTemp;
	bool ok;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("Kasabada alarm verilmiş. Görünüşe bakılırsa, artık benim de silaha sarılma vaktim geldi...","Şehir muhafızları seni tesadüfen kovalamıyor mu, yoksa?","Burada sığınacak bir yer bulamazsın, ama kaburgalarının altına birkaç santim soğuk çelik saplanabilir!"),LinkRandPhrase("Ne istiyorsun, "+GetSexPhrase("alçak","serseri")+"?! Muhafızlar peşinde, fazla uzağa gidemezsin, "+GetSexPhrase("pislik korsan","pislik")+"!",""+GetSexPhrase("Pis","Pis")+" Katil! Muhafızlar!!!","Senden korkmuyorum, "+GetSexPhrase("sürüngen","pislik")+"! Çok yakında kalemizde asılacaksın, fazla uzağa gidemezsin..."));
				link.l1 = PCharRepPhrase(RandPhraseSimple("Yaşamaktan bıktığını görüyorum...","Demek ki, burada barışçıl insanlar yokmuş "+XI_ConvertString("Colony"+npchar.city+"Gen")+", herkes kahraman olmak istiyor!"),RandPhraseSimple("Cehenneme git!","Heh,   bunlar   hayatının   son   birkaç   saniyesi   olacak..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			//belamour legendary edtion карибские нравы
			if(npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
			{
				dialog.text = "Bu defa seni bana getiren nedir?";
				link.l1 = "Gerard LeCroix adında bir beyefendiyi tanıdığınızı düşünüyorum. Bana bir ödül bırakmış olmalı...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("İyi günler, denizci! Benim adım "+GetFullName(npchar)+", ve ben bu deniz fenerinin bekçisiyim. Hangi rüzgar seni buraya getirdi?","Merhaba! Fenerimde yeni yüzler görmeyeli epey zaman oldu... Kendimi tanıtmama izin verin - "+GetFullName(npchar)+", ve bu deniz feneri hem evim hem de işim. Size nasıl yardımcı olabilirim?");
				link.l1 = "Merhaba, "+npchar.name+"! Benim adım "+GetFullName(pchar)+", Ben bir gemi kaptanıyım. Bu harika koyda dolaşıyordum ve burada kimlerin yaşadığını görmek için uğramaya karar verdim.";
				link.l1.go = "Lightman_meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, eski dostum, Kaptan "+GetFullName(pchar)+" ! Buyurun, buyurun! Bu sefer sizi buraya ne getirdi?";
				link.l1 = "Selam sana, ihtiyar deniz kurdu! Burada fenerinde yalnız başına inleyip durmuyor musun?";
				link.l1.go = "Lightman_talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_meeting":
			dialog.text = "Artık biliyorsun. Ben de senin gibi bir zamanlar denizciydim, ama bir geminin güvertesine adım atmayalı çok uzun zaman oldu. Şimdi bu deniz feneri bana emanet, ayrıca birkaç şey de satıyorum...";
			link.l1 = "Ve tam olarak ne satıyorsun?";
			link.l1.go = "trade_info";
			NextDiag.TempNode = "First time";
		break;
		
		case "Lightman_talk":
			dialog.text = " Bu sefer seni buraya ne getirdi?";
			link.l1 = RandPhraseSimple("Son zamanlarda koloninizde ilginç bir şey oldu mu, anlatabilir misiniz?","Uzun zamandır karaya ayak basmadım... Burada neler oluyor?");
			link.l1.go = "rumours_lighthouse";
			link.l2 = "Ne sattığını görelim.";
			link.l2.go = "Trade_lighthouse";
			if (CheckAttribute(npchar, "artefact"))
			{
				if (CheckAttribute(npchar, "quest.art"))
				{
					link.l3 = "Yani, "+npchar.name+", tılsımım çoktan geldi mi?";
					link.l3.go = "Trade_artefact_3";
				}
				else
				{
					link.l3 = ""+npchar.name+", senden bir muska sipariş etmek istiyorum.";
					link.l3.go = "Trade_artefact_1";
				}
				// калеуче
				if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
				{
					link.l5 = "Dinle, "+npchar.name+", sipariş üzerine muska temin ettiğini biliyorum. O halde, onlar hakkında çok şey biliyor olmalısın. Lütfen, şu küçük şeye bir bakar mısın - bana bunun hakkında ne söyleyebilirsin?";
					link.l5.go = "Caleuche";
				}
				if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
				{
					link.l5 = "Dostum, yine geldim, şu garip muskalar hakkında sana bir şey sormak istiyorum";
					link.l5.go = "Caleuche_9";
				}
			}
			link.l4 = "Sana bir şey soracaktım...";
			link.l4.go = "quests";
			link.l9 = "Az önce bir göz attım...";
			link.l9.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "Bazen kıyıya giderim ve deniz kabukları toplarım, burada pek uzakta olmayan güzel bir yer var, bu yüzden benden her zaman inci satın alabilirsin. Her fırtına kehribar getirir, onu da satarım ama pahalıya mal olur.\nBazen dalgalar batık gemilerden her türlü ilginç ıvır zıvırı kıyıya atar, eski dostlarım da bana özel eşyalar getirir. Büyülü muskalar ilgimi çeker, bilge adamlar onlara iyi para öder.\nBazen özel günlerde silah da satarım, nereden bulduğumu sorma. Kasaba tüccarı benden tüm ıvır zıvırı alır, iyi şeyleri ise tamir edip temizledikten sonra kendim satarım.\nRom ilgimi çeker. Yerel meyhanede iki pesoya bir kupa verdikleri pis sudan bahsetmiyorum. Gerçek, şişelenmiş Jamaika romundan söz ediyorum. O, insanı iyileştirir ve hayata döndürür. Getirdiğin her şişe için on katı öderim. Bir düşün.";
			link.l1 = "Dinle, "+npchar.name+", eski denizci dostlarınızın size büyülü tılsımlar getirdiğinden bahsetmiştiniz. Sizden özel bir tılsım sipariş etmem mümkün mü? Bunun için size iyi bir ödeme yaparım.";
			link.l1.go = "Trade_artefact";
		break;
		
		case "Trade_lighthouse":
			//иногда продает корабельные товары // Addon-2016 Jason
			npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
			npchar.quest.goodsqty = 50+hrand(100);
			if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY) npchar.quest.goodsqty = 25+hrand(50);
			npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost)/4);//цена единицы товара
			npchar.quest.goodscost = sti(npchar.quest.goodsprice)*sti(npchar.quest.goodsqty);//стоимость товара
			ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10)
			if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
			{
				dialog.text = "Kaptan, yakın zamanda bir miktar mal kıyıya vurdu - "+GetGoodsNameAlt(sti(npchar.quest.goods))+". Bazı kısımlar tuzlu suyla mahvolmuş, ama "+FindRussianQtyString(sti(npchar.quest.goodsqty))+" Onları çok iyi durumda kurtardım. Satın almak ister misin? Sadece senin için ucuza veririm "+FindRussianMoneyString(sti(npchar.quest.goodsprice))+" birim başına.";
				link.l1 = "Hayır. Son topladıklarını göster bana.";
				link.l1.go = "Trade_lighthouse_double";
				link.l2 = "Hm... Dürüst bir teklif, kabul ediyorum. Sanırım bunu biraz kârla tekrar satabilirim. Bakalım... Toplamda tutarı şu olacak "+FindRussianMoneyString(sti(npchar.quest.goodscost))+" . Doğru mu?";
				link.l2.go = "Trade_goods";
				SaveCurrentNpcQuestDateParam(npchar, "goods_date");
			}
			else
			{
				DialogExit();
				if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
				{
					GiveItemToTrader(npchar);
					SaveCurrentNpcQuestDateParam(npchar, "trade_date");
				}
				LaunchItemsTrade(npchar, 0);
			}
		break;
		
		case "Trade_lighthouse_double":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		break;
		
		case "Trade_goods":
			AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
			AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
			AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
			dialog.text = "Doğru bildiniz, kaptan. Harika bir anlaşma! İkimiz de bundan güzel bir kazanç sağladık...";
			link.l1 = "Pekâlâ, o zaman. Tayfaları yükü gemime taşımaları için göndereceğim. Şimdi, satışa ne topladığını göster bana.";
			link.l1.go = "Trade_lighthouse_double";
		break;
//------------------------------------------------заказ артефактов------------------------------------------------
		case "Trade_artefact":
			if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
			{
				dialog.text = "Pekala, hepsi değil ama bazı tılsımlar diğerlerinden daha sık gelir, bu yüzden sana yardımcı olabilirim sanırım. Ama uyarıyorum: bu şekilde sipariş edilen tüm muskalar sana 100 dublona mal olacak. Anlamalısın ki...";
				link.l1 = "Fiyat sorun değil. Hangi tılsımları sunabilirsin?";
				link.l1.go = "Trade_artefact_1";
				link.l2 = "Peh! O parayla bir gemi alınır. Bu çok pahalı. Sanırım kendi başıma da idare ederim...";
				link.l2.go = "exit_artefact";
			}
			else
			{
				dialog.text = "Hayır, kaptan. Böyle şeyler ancak şans eseri bulunur, önceden sipariş vermek imkânsız. Üstelik, onları beklemeniz neredeyse sonsuzluk kadar sürer...";
				link.l1 = "Pekala, öyleyse yapılacak bir şey yok.";
				link.l1.go = "exit_artefact";
			}
		break;
		
		case "exit_artefact":
			if (CheckAttribute(npchar, "artefact")) dialog.text = "Dediğiniz gibi. Fikriniz değişirse yanıma gelin.";
			else dialog.text = "Bugün satışta nelerim var görmek ister misiniz, kaptan? Eğer ilginizi çeken bir şey bulamazsanız, yakında tekrar uğrayın – belki başka bir şey bulabilirsiniz.";
			// belamour legendary edition карибские нравы -->
			if(CheckAttribute(npchar, "quest.trial_usurer"))
			{
				link.l1 = "Tüm bunlar elbette güzel, ama asıl sormak istediğim şu – sanırım Gerard Lecroix adında bir beyefendiyi tanıyorsunuzdur? Bana bir ödül bırakmış olması gerekiyordu...";
				link.l1.go = "Trial";
				DelLandQuestMark(npchar);
				break;
			}
			// <-- legendary edition
			link.l1 = "Eşyalarını göster.";
			link.l1.go = "Trade_lighthouse";
			link.l2 = "Bana sadece söyle, son zamanlarda koloninizde ilginç neler oldu?";
			link.l2.go = "rumours_lighthouse";
			link.l3 = "Ticaret ticarettir, ama bir şey sormak istedim.";
			link.l3.go = "quests";
			link.l4 = "Güzel bir gün geçir, "+npchar.name+"! Tanıştığımıza memnun oldum! Başka bir zaman uğrarım...";
			link.l4.go = "exit";
		break;
		
		case "Trade_artefact_1":
			dialog.text = "Seçimini yap.";
			iTemp = 1;
			string sArt;
			if (CheckAttribute(npchar, "artefact.indian")) sArt = "indian_";
			if (CheckAttribute(npchar, "artefact.amulet")) sArt = "amulet_";
			if (CheckAttribute(npchar, "artefact.obereg")) sArt = "obereg_";
			for (i=11; i>=1; i--)
			{
				sTemp = "l"+iTemp;
				link.(sTemp) = XI_ConvertString(sArt+i);
				link.(sTemp).go = sArt+i;
				iTemp++;
			}
			link.l12 = "Ne yazık ki, bu listedekilerden hiçbiri şu ana kadar ilgimi çekmedi.";
			link.l12.go = "exit";
		break;
		
		//группа indian
		case "indian_1":
			dialog.text = "Bir vudu bebeği mi? Ateşli silahları sever misin? Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_1";
		break;
		
		case "indian_2":
			dialog.text = "Barut testçisi mi? Her çatışmada başarıya giden yol keskin nişancılıktan geçer. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_2";
		break;
		
		case "indian_3":
			dialog.text = "Ritüel bir bıçak mı? Düşmanlarını ağır bir pala ile güçlü darbelerle parçalamayı mı seversin? O zaman bu tam sana göre. Güzel... ";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_3";
		break;
		
		case "indian_4":
			dialog.text = "Bir balta mızrağı mı? Kocaman bir baltayla yukarıdan indirilen bir darbe, her düşmanı ezer! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_4";
		break;
		
		case "indian_5":
			dialog.text = "Bir tsantsa mı? O şey en gözü kara korsanı bile korkutabilir. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_5";
		break;
		
		case "indian_6":
			dialog.text = "Bir mercan kayası mı? Toplarınızdan çıkan saçma doğrudan hedefe gidecek! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_6";
		break;
		
		case "indian_7":
			dialog.text = "Humpback? Yorulmak bilmemek bir savaşçının en iyi dostudur. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_7";
		break;
		
		case "indian_8":
			dialog.text = "Xiuhtecuhtli mi? Düşman gemisinin gövdesi toza dönüşsün! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_8";
		break;
		
		case "indian_9":
			dialog.text = "Baldo mu? Baldo'yu yerleştir – her top mermisi tam isabet eder! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_9";
		break;
		
		case "indian_10":
			dialog.text = "Cascavella mı? Yılan zehiri en tehlikeli şeydir. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_10";
		break;
		
		case "indian_11":
			dialog.text = "Ngombo maskesi mi? Düşmanlarının tetikte olmasını azaltır, ha-ha! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "indian_11";
		break;
		
		//группа amulet
		case "amulet_1":
			dialog.text = "Ngombo kalkanı mı? Eğer bir kurşaktan kaçamadıysan, bu tılsım hayatını kurtarabilir. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_1";
		break;
		
		case "amulet_2":
			dialog.text = "Euchologion mu? İyi bir dua kurşunu bile saptırabilir. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_2";
		break;
		
		case "amulet_3":
			dialog.text = "Bir haç mı? Bu, bir Hristiyan'a yakın dövüşte büyük fayda sağlar. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_3";
		break;
		
		case "amulet_4":
			dialog.text = "El Trozo mu? Bu yara ölümcülken sadece bir çizik olacak. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_4";
		break;
		
		case "amulet_5":
			dialog.text = "Sogbo? Ve toplar her zaman savaşa hazır olsun! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_5";
		break;
		
		case "amulet_6":
			dialog.text = "Madonna mı? En Kutsal Bakire'nin yüzü güçlü iyileştirici özelliklere sahip. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_6";
		break;
		
		case "amulet_7":
			dialog.text = "Kutsal su mu? Kutsal suyla serpilmiş bir zavallı bile destansı bir kahramana dönüşür! Güzel...";
			link.l1 = "Siparişimi almak için ne zaman geri gelmeliyim?";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_7";
		break;
		
		case "amulet_8":
			dialog.text = "Bir çapa mı? Gemin, top mermileri yağsa bile su üstünde kalsın, ha-ha! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_8";
		break;
		
		case "amulet_9":
			dialog.text = "Enkolpion mu? Bu muska sende olduğu sürece yelkenlerin hiçbir rüzgardan korkmaz. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_9";
		break;
		
		case "amulet_10":
			dialog.text = "Mucize yaratan mı? Tanrı hem karada hem de denizde tayfanızın yanında olsun! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_10";
		break;
		
		case "amulet_11":
			dialog.text = "Cimaruta mı? Tüfek mermileri başının üzerinden geçecek, sana hiçbir zarar vermeyecek! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "amulet_11";
		break;
		
		//группа obereg
		case "obereg_1":
			dialog.text = "Teredo mu? Her gemi ustasının hayalini süsler o. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_1";
		break;
		
		case "obereg_2":
			dialog.text = "Xochipilli mi? Bu, yelkenleri yamamada biraz zaman kazandıracak. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_2";
		break;
		
		case "obereg_3":
			dialog.text = "Maymun mu? Bence tam bir yük katırı! Güzel...";
			link.l1 = "   Siparişimi almak için ne zaman geri gelmeliyim?   ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_3";
		break;
		
		case "obereg_4":
			dialog.text = "Çingene hayranı mısın? Bir devriyenin gözünü boyadın! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_4";
		break;
		
		case "obereg_5":
			dialog.text = "Yeşim bir kaplumbağa mı? Bu senin elindeki koz! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_5";
		break;
		
		case "obereg_6":
			dialog.text = "Maymun yumruğu mu? Derler ya - kendini saydır! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_6";
		break;
		
		case "obereg_7":
			dialog.text = "Bir balıkçı mı? Bu her denizcinin hayali. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_7";
		break;
		
		case "obereg_8":
			dialog.text = "Tüccarın boncukları mı? Para sayılmayı sever, değil mi? Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_8";
		break;
		
		case "obereg_9":
			dialog.text = "Ehecatl mi? En yavaş, eski bir tekne bile rüzgardan hızlı gider! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_9";
		break;
		
		case "obereg_10":
			dialog.text = "Denizcinin küpesi mi? Onu dümencine ver! Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_10";
		break;
		
		case "obereg_11":
			dialog.text = "Hacı mı? Karşıdan esen rüzgar arkadan esmeye başlar. Güzel...";
			link.l1 = " Siparişimi almak için ne zaman geri gelmeliyim? ";
			link.l1.go = "Trade_artefact_2";
			npchar.quest.art = "obereg_11";
		break;
		
		case "Trade_artefact_2":
			dialog.text = "İki ay sonra, daha erken değil. O zamana kadar bana getireceklerini düşünüyorum. Yani iki ay sonra seni parayla bekliyor olacağım.";
			link.l1 = "Harika! Orada olacağım! Teşekkür ederim, "+npchar.name+"!";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "art_date");
			npchar.quest.artday = rand(20)+50;
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "1");
			ReOpenQuestHeader(sTemp);
			AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;
		
		case "Trade_artefact_3":
			if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
			{
			dialog.text = "Evet, bende var. Yüz dublon hazırladın mı, Kaptan?"; // Addon-2016 Jason
				// belamour legendary edition -->
				if(PCharDublonsTotal() >= 100) 
				{
					link.l1 = "Tabii! Buyurun, anlaştığımız gibi.";
					link.l1.go = "Trade_artefact_4";
				}
				else
				{
					link.l1 = "Ah, parayı gemide unuttum! Hemen getiririm.";
					link.l1.go = "exit";
				}
				// <-- legendary edition
			}
			else
			{
			dialog.text = "Henüz değil. Sonra tekrar gel. Merak etme – muskan mutlaka eline ulaşacak.";
			link.l1 = "Pekala.";
			link.l1.go = "exit";
			}
		break;
		
		case "Trade_artefact_4":
			RemoveDublonsFromPCharTotal(100); // Addon-2016 Jason
			Log_Info("You have given 100 doubloons");
			dialog.text = "Her şey yolunda görünüyor. İşte tılsımın, sana uğur getirsin!";
			link.l1 = "Teşekkür ederim, "+npchar.name+"!";
			link.l1.go = "Trade_artefact_5";
		break;
		
		case "Trade_artefact_5":
			DialogExit();
			Log_Info("You have received "+XI_ConvertString(npchar.quest.art)+"");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, npchar.quest.art, 1);
			DeleteAttribute(npchar, "quest.art");
			sTemp = "Amulet_"+npchar.location;
			AddQuestRecord(sTemp, "2");
			CloseQuestHeader(sTemp);
		break;
		
		// --> калеуче
		case "caleuche":
			PlaySound("interface\important_item.wav");
			dialog.text = "Bana orada neyin var göster.";
			link.l1 = "Bak, bu eski bir Hint tılsımına benziyor. Ama nasıl kullanılacağını ya da içinde hangi gizli gücün saklı olduğunu hiç bilmiyorum.";
			link.l1.go = "caleuche_1";
			npchar.quest.caleuche = "true";
		break;
		
		case "caleuche_1":
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
			{
				dialog.text = "Pekâlâ, pekâlâ. Bana böyle bir şeyi gösteren üçüncü kişisin, dostum. Bu muska buraya Güney Ana'nın vahşi ormanlarından getirildi. Panama yakınlarında, bunun gibi takılar takan Kızılderililer var. Kızıl derililer bunun 'büyük atalarının' mirası olduğunu söylüyorlar.\nAtalarının kim olduğunu ya da ne tür bir miras bıraktıklarını hiç bilmiyorum, ama sana nerede soruşturabileceğin konusunda bir tavsiye verebilirim. İlgilenir misin?";
				link.l1 = "Elbette!";
				link.l1.go = "caleuche_2";
				DelLandQuestMark(npchar);
				if (npchar.id == "BasTer_Lightman") DelMapQuestMarkShore("Mayak4");
				if (npchar.id == "Santiago_Lightman") DelMapQuestMarkShore("Mayak9");
			}
			else
			{
				dialog.text = "Hmm... I've held a lot of amulets in my hands, but this one, I see for the first time in the Caribbean. Sorry, mate, I cannot help you; I don't know this kind of stuff. But it is not a simple thing; that's a fact. Ask somebody else. I know for sure that there are other lighthouse keepers like me who know about amulets not any less.";
				link.l1 = "Affedersiniz... O zaman sormaya devam edeceğim.";
				link.l1.go = "exit";
			}
		break;
		
		case "caleuche_2":
			dialog.text = "There is a Carib village on Dominica, and the local chief is named Moknitekuvri. They have a shaman named Tuttuathapak, a highly respected Indian. He's not one of the Caribs; he's from that place about which I've told you already. He can tell you more about this amulet than me. But be careful - Tuttuathapak hates white people. He really hates them. After all, they once enslaved him and took him away from his home...";
			link.l1 = "Sanırım o da bu şekilde Karayiplere geldi, değil mi?";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			dialog.text = "Evet. Oldukça ilginç bir hikaye bu. Hintli köleleri taşıyan gemi, Marie Galante yakınlarında tam bir durgunluğa yakalandı ve mürettebatın yarısı aniden çıkan bir hastalıktan öldü. Ama tek bir Hintli bile hastalanmadı!\nSonrasında kaptan delirdi ve gemisini ateşe verdi. Bunun sonucunda, hapsedilen Hintliler isyan çıkarıp mürettebatı katlettiler. Sence onların lideri kimdi?";
			link.l1 = "Ben kabul ediyorum...";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			dialog.text = "Hepsi bu. Eminim denizi ölü gibi sakinleştiren ve tayfayı ölümcül bir hastalıkla bulaştıran bir şaman büyüsüydü. Bu Kızılderili çok zeki ve çok tehlikeli. Ona gidersen - kibar davran ve ağzından çıkanlara dikkat et - yoksa başın büyük belaya girer. Ayrıca, ona bir hediye götürmezsen seninle konuşmaz bile.";
			link.l1 = "Peki, ne tür bir adak isteyebilir?";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			dialog.text = "Ona birkaç değersiz şeyle rüşvet veremezsin. Bildiğim kadarıyla, Carib askerlerini beyaz yerleşimlere tüfek almaya gönderiyor. Ona hediye olarak bir misket tüfeği götür, o zaman sanırım memnun kalır ve sana biraz ilgi gösterir.";
			link.l1 = "Teşekkür ederim! Dediğiniz gibi yapacağım... Söyler misiniz, bunların hepsini nasıl biliyorsunuz?";
			link.l1.go = "caleuche_6";
		break;
		
		case "caleuche_6":
			dialog.text = "Benim arkadaşım o talihsiz gemide denizciydi. Neyse ki, o cehennemden sağ çıkmayı başardı... Üzerinde seninkine benzeyen bir muska gördüm, demek ki merhum kaptan da bazı yerlilere ait eşyaları almış. Eminim muskan onun koleksiyonundan – kaptan delirdiğinde ve gemisini ateşe verdiğinde, tayfası onu öldürüp kamaradaki sandıkları yağmalamış.";
			link.l1 = "Anlaşıldı. O zaman Dominika'ya sadece bir hediye götürmem gerekiyor. Yardımın ve ilginç hikayen için teşekkürler!";
			link.l1.go = "caleuche_7";
		break;
		
		case "caleuche_7":
			dialog.text = "İyi şanslar, dostum, ve bu kızıl derili şeytana dikkat et...";
			link.l1 = "...";
			link.l1.go = "caleuche_8";
		break;
		
		case "caleuche_8":
			DialogExit();
			AddQuestRecord("Caleuche", "2");
			pchar.questTemp.Caleuche = "dominica"; 
			Caleuche_CreateShamane();
		break;
		
		case "caleuche_9":
			dialog.text = "Evet? Tuttuathapak ile konuştun, değil mi?";
			link.l1 = "Kesinlikle. Şimdi ise iki muska daha bulmak istiyorum. Bu eseri sana gösteren üçüncü kişi olduğumu söyledin. Peki, diğer ikisi kimdi?";
			link.l1.go = "caleuche_10";
			DelLandQuestMark(npchar);
		break;
		
		case "caleuche_10":
			dialog.text = "Biri arkadaşım, o gemideki denizci; Tuttuathapak'ı Karayip adalarına getiren gemi. O olaydan beri hiçbir geminin güvertesine adım atmadı. Bir süredir onu görmedim ama nerede yaşadığını biliyorum. Onu Batı Ana Kara'da, Belize'de ara – artık avcı oldu ve ormanlarda dolaşıyor. Adı Fergus Hooper.";
			link.l1 = "Pekala.   Ya ikincisi?";
			link.l1.go = "caleuche_11";
		break;
		
		case "caleuche_11":
			dialog.text = "İkinci hakkında çok az şey biliyorum. Adı Jack mi, Jackson mı, özel korsan mı, küçük bir tüccar mı, yoksa sadece bir maceraperest mi, emin değilim. Tuhaf isimli bir zebek gemisi var... hmm... adı... Kahretsin, unuttum! Ama adı şeytani bir şeydi. Ona ne anlama geldiğini sordum, o da deniz tanrılarından doğmuş bir kuş-kadın olduğunu söyledi. Hah! Dinsiz...";
			link.l1 = "İnek... Yani adını hatırlamıyor musun?";
			link.l1.go = "caleuche_12";
		break;
		
		case "caleuche_12":
			dialog.text = "Hayır, yıldırım çarpsın beni, hatırlamıyorum. Ah, ve kendini tanıttığında Barbados'tan olduğunu söylemişti.";
			link.l1 = "Bu da bir şey! Peki, tüy meraklısı kadınların aşığını başkası bulmadan önce ben bulmaya çalışacağım... Sağ ol dostum, bana çok yardımcı oldun!";
			link.l1.go = "caleuche_13";
		break;
		
		case "caleuche_13":
			dialog.text = "Rica ederim Kaptan, bir ara uğra.";
			link.l1 = "Tabii!";
			link.l1.go = "caleuche_14";
		break;
		
		case "caleuche_14":
			DialogExit();
			AddQuestRecord("Caleuche", "7");
			pchar.questTemp.Caleuche = "hunting"; 
			pchar.questTemp.Caleuche.Belizterms = rand(4)+3;
			pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
			pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
			pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
			AddLandQuestMark(characterFromId("Bridgetown_Portman"), "questmarkmain");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда		   
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("Sen "+GetSexPhrase(" bir hırsız, canım! Muhafızlar, yakalayın onu"," Hırsız! Muhafızlar, onu yakalayın")+"!!!","Vay canına! Bir an gözümü çevirdim, sen çoktan sandığın içine dalmışsın! Dur, hırsız!","Gardiyanlar! Soygun var! Hırsızı durdurun!");
			link.l1 = "Lanet olsun!";
			link.l1.go = "fight";
		break;
		
		// belamour legendary edition карибские нравы
		case "Trial":
			dialog.text = "Ah, demek o kaptan sensin! Evet, seni bekliyordum. Gerard da bekliyordu ama acil bir keşif için ayrılması gerekti, bu yüzden ödemeyi sana teslim etmemi istedi. Mutlaka gelmen gerektiğini söyledi. Burada 90 dublon var, lütfen buyur.");
			link.l1 = "Teşekkür ederim! Dürüst insanlarla iş yapmak güzel.";
			link.l1.go = "Trial_1";
		break;
		
		case "Trial_1":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 90);
            NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(pchar, "questTemp.Trial");
			DeleteAttribute(npchar, "quest.trial_usurer");
			pchar.questTemp.IslamonaSpaOfficer = true;
			CloseQuestHeader("Trial");
			pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}
