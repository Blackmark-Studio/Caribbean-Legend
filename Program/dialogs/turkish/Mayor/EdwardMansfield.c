// Эдвард Мэнсфилд, глава буканьеров и авторитетный пират, английская линейка
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    
// ============================================================================
// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                break;
            }
        }
    }
// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
// ============================================================================
	switch(Dialog.CurrentNode)
	{
		case "First time":
            NextDiag.TempNode = "First time";
            if (CheckAttribute(npchar, "Sp5LaVegaAttackDone"))
            {
            	if (NPChar.quest.meeting == "0")
				{
					dialog.Text = TimeGreeting()+"! Ben "+GetFullName(NPChar)+", bu bataklığın yeni valisi. Buradaki serserileri yola getirmek kolay olmayacak, ama artık İspanyol kolonilerine tehdit oluşturmuyorlar.";
					Link.l1 = "Sizinle tanıştığıma memnun oldum. Ben Kaptan "+GetFullName(Pchar)+". Üzgünüm, ama gitmeliyim.";
					Link.l1.go = "exit";
					NPChar.quest.meeting = "1";
				}
				else
				{
					dialog.Text = TimeGreeting()+". Meşgulüm, gerçekten çok meşgulüm, İspanyol kolonilerine yönelik herhangi bir tehdidi önlemek için buradaki serserileri kontrol altında tutmam gerekiyor.";
					Link.l1 = "O zaman seni rahatsız etmeyeceğim.";
					Link.l1.go = "exit";
				}
            }
            else
            {
				dialog.text = NPCStringReactionRepeat("Bana söyleyecek bir şeyin var mı? Yok mu? O halde "+GetSexPhrase("Defol buradan!","Rica ediyorum, beni rahatsız etmeyin.")+"","Sanırım kendimi yeterince açık ifade ettim...","Ne kadar açık konuşsam da, beni rahatsız etmeye devam ediyorsun!","Eh, sen gerçekten eşsizsin "+GetSexPhrase("çok kaba, mon chéri","böyle bir saygısızlık, kızım","ne biçim terbiyesizlik bu, kız")+"...","repeat",30,npchar,Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("Gidiyorum.","Evet, "+npchar.name+", görüyorum.","Üzgünüm, "+npchar.name+"...","Ah...",npchar,Dialog.CurrentNode);
				link.l1.go = "exit";
			}


					if (npchar.city == sti(pchar.HeroParam.Location))
					{
						if(!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
						{
							link.l2 = "Benim için bir işin var mı?";
							link.l2.go = "pirateStartQuest";
						}
						else
						{
							if(pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many"))
							{
								link.l2 = "İzi buldum, ama o sıçanı deliğinden çıkarmak için biraz paraya ihtiyacım var — 30.000 peso lazım.";
								link.l2.go = "pirateStartQuest_many";	
							}
							if(pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "letter_open") > 0)
							{
								link.l2 = "Bak, kaçakçının cesedinde bulduğum şu mektuba bir göz at";
								link.l2.go = "pirateStartQuest_info_1";	
							}
							if(pchar.questTemp.pirateStartQuest == "5")
							{
								link.l2 = "İş bitti. Norman Vigo ve gemisi artık deniz şeytanına ait.";
								link.l2.go = "pirateStartQuest_final";	
							}
						}
					}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = "Hm... İş mi diyorsun? Aslında, sorduğun iyi oldu. Dışarıdan birine ihtiyacım var. En yakın kasabada bir şey öğrenmek istiyorum ama adamlarım orada tanınıyor. Sana çok bir şey vaat edemem, ama bir şeyler alırsın.";
			link.l1 = "Görev ne?";
			link.l1.go = "pirateStartQuest_1";
			link.l2 = "Üzgünüm, ama birkaç kırıntı için bu riski almam. Hoşça kal.";
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
		break;
		case "pirateStartQuest_1":
			dialog.text = "O zaman dinle, bir ay önce 'Saintblue' adlı şalopa kaptanıyla 200 köle teslim etmek için bir anlaşma yaptım. Onları yerel plantasyon sahibine satmayı planlıyordum. Süre doldu ve müşteri endişelenmeye başladı, ama dün bana şalopanının adaya yakın bir yerde görüldüğü söylendi. Ama! Kaptan ortada yoktu. Bugün müşterim avansını geri istedi ve başka bir satıcıdan köle teklif edildiğini söyledi. Daha pahalı, ama tüm köleler bir seferde.";
			link.l1 = "Ee? Birkaç gün içinde seni avans kaybından kurtarmak için 200 köle mi bulmam gerekiyor? Birkaç kuruş için mi?";
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = "Tabii ki hayır. Aptal gibi mi görünüyorum? Avansı ona asla geri vermem. Ama bana sunulan kölelerin gerçekten benim olduğuna dair kanıt lazım. Ona yeni bir anlaşma teklif edenleri bul, 10.000 peso senin olur. Anlaştık mı?";
			link.l1 = "Varım. Sence kim olabilir, bir şüphen var mı?";
			link.l1.go = "pirateStartQuest_3";
			link.l2 = "Hiç şansın yok. Başkasını bul, sadece 10.000 için mi? Kusura bakma, olmaz.";
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = "Eğer bir fikrim olsaydı, senin hizmetlerine asla başvurmazdım. O adamlar şimdiye kadar çoktan ölmüş olurdu. Ama 'Saintblue'un yükü ve müşterim hakkında nasıl bilgi edindiklerini öğrenmek istiyorum. Görünen o ki, bu onlar için oldukça kolay olmuş. Şimdi anlıyor musun?";
			link.l1 = "Evet, birisi sana ihanet etmiş.";
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.Name = GetFullName(npchar);

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);
		break;
		case "pirateStartQuest_4":
			dialog.text = "Kesinlikle! Onu arıyorum. Rakiplerimi öldürmek ya da kölelerimi geri getirmek senin önceliklerin değil. O sıçanı istiyorum—daha doğrusu, dürüst olmak gerekirse, kafasını bir kazığa geçirmek istiyorum. Şimdi adamlarımın görevin hakkında hiçbir şey bilmemesi gerektiğini anlıyor musun? Bilgileri kimin sattığını bulana kadar herkesten şüpheleneceğim. Ve açıkçası, bunu hiç istemiyorum...";
			link.l1 = "Anladım. O zaman sessiz kalacağım. Yoldayım.";
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = "Otuz bin mi diyorsun? Bu büyük bir meblağ... Sana en fazla 5.000 peso verebilirim, şu anda elimde olan bu. Sakın parayı alıp kaçmayı aklından bile geçirme, yoksa seni bulur, en yakın çite asarım! Anladın mı?";
			link.l1 = "Pekâlâ, o zaman bana beş bin ver...";
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = "Al onu. Aramanın sonucunu bekliyorum.";
			link.l1 = "Her şey yoluna girecek.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = "Ha! Harika haber! Başaracağına emindim. Elimde ilginç bilgiler var.";
			link.l1 = "İşimi bitirdim ve on binimi istiyorum.";
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "letter_open");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = "Elbette, işte ödülün. Ama kaçma, senin için bir görevim daha var.\nPfaifer, 'Septima' adlı luggerin tayfası ve Norman Vigo'nun adamı. Norman Vigo'nun bir hain olduğuna eminim, aramızdan biri olsa bile. Son zamanlarda adanın yakınlarındaki sularda görülmüş. Senin işin, bu sıçanı deniz şeytanına göndermek. İlk seferinde beni hayal kırıklığına uğratmadın, bu işi de sana emanet etmek istiyorum. Sana 15.000 peso ödeyeceğim. Anlaştık mı?";
			link.l1 = "Ben hallederim! Hainin öldüğünü farz et.";
			link.l1.go = "pirateStartQuest_info_3";
			link.l2 = "Biliyor musun, bunun bir parçası olmak istemiyorum... Zaten vaktim yok. Kusura bakma, ama gidiyorum.";
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", pchar.questTemp.pirateStartQuest.Name);

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = "Biliyorum, biliyorum. Adamlarım savaşı izliyordu ve kusursuz zaferini bana çoktan bildirdiler. Pekala, işini iyi yaptın. Söz verdiğim gibi, işte 15.000 peso. Ve teşekkür ederim, bana gerçekten çok yardımcı oldun.";
			link.l1 = "Önemli değil, yardımcı olduğuma sevindim! Ama artık gitmem gerek, burada fazla kaldım ve yapacak çok işim var. Hoşça kal!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
		break;
				
 		case "No_Mansfield_first_time":
			dialog.text = "Selam, adım Alistair Good. Mansfield öldükten sonra korsanların başı olarak seçildim.";
			link.l1 = "Tanıştığıma memnun oldum, Alistair.";
			link.l1.go = "exit";
			NextDiag.TempNode = "No_Mansfield";
  		break;
 		case "No_Mansfield":
			dialog.text = "Seninle konuşacak vaktim yok. Sonra gel.";
			link.l1 = "Zaten gidiyorum.";
			link.l1.go = "exit";
  		break;
		

// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+GetSexPhrase("Al ","Al ")+" dışarı!","Defol evimden!");
			link.l1 = "Hay aksi...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Мэнсфилдом через 30 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Beni rahatsız etme, bunu unutma.";
        			link.l1 = "Anladım.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LaVega_town","reload","reload6");
		break;
// <<<<<<<<<<<<============= блок нод angry =============================
	}
}
