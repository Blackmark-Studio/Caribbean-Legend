// Слухи - диалог по типажам

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	bool bOk1, bOk2;
	switch(Dialog.CurrentNode)
	{
/////////////////////////////////////////////////---слухи мещанок---////////////////////////////////////////////
		case "rumours_towngirl":	
		NextDiag.CurrentNode = "rumours";
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Você ficou sabendo? Dizem que a filha do Thomas Morrison está de cama faz seis meses já. Os médicos não conseguem fazer nada contra a doença dela. A única que pode ajudar é a cigana famosa pelas poções que curam até os mais doentes. Mas ela se recusou completamente a fazer qualquer coisa pela pobre moça.";
			link.l1 = "Obrigado, preciso me retirar.";
			link.l1.go = "exit";
			DWH_Start();
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Dois dias atrás, tentaram matar o Chefe do Porto na maior cara de pau! O assassino ficou esperando na porta do escritório dele, mas o Chefe conseguiu gritar por socorro. Um mosqueteiro chegou correndo e feriu o canalha, mas o sujeito ainda escapou pelos portões da cidade\nDizem que o Chefe do Porto está oferecendo uma bela recompensa pela cabeça desse bandido! Até agora, ninguém teve coragem de se apresentar.";
			link.l1 = "Obrigado, preciso ir agora.";
			link.l1.go = "exit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Ouviu as novidades?! Isso é um absurdo dos grandes! Não sobrou uma gota de rum ou vinho na taverna – como é que alguém vai se aliviar nesse calor dos infernos? O estalajadeiro vive nos enchendo de promessas vazias há uma semana dizendo que a bebida vai voltar, mas até agora, nada! Querem que a gente fique com a garganta seca até o fim dos tempos?";
			link.l1 = "Obrigado, preciso ir agora.";
			link.l1.go = "exit";
			TPZ_Start();
			break;
        }
		//<-- Торговля по закону
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
		{
			dialog.text = "Dizem por aí no porto que Julie d'Armagnac, sobrinha do governador, virou só uma sombra do que já foi. Antes cheia de vida e radiante, agora vaga pelas ruas com uma tristeza estampada no rosto. O povo comenta e tenta adivinhar o que aconteceu com ela, mas ninguém sabe ao certo. Vai ver algum canalha partiu o coração dela?"+GetSexPhrase(" Será que foi você, capitão?","")+"";
			link.l1 = ""+GetSexPhrase("Duvido ","")+". Obrigado, preciso me retirar.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Dizem que o pescador Pierre Carno sumiu sem deixar rastro. Dois dias atrás, ele saiu para o mar e desde então não se teve mais notícia dele. A esposa dele, Lea, está inconsolável. De dia e de noite, ela fica de vigia no cais, com os olhos perdidos no horizonte, rezando para ver a vela do marido voltar.";
			link.l1 = "Obrigado, preciso me retirar.";
			link.l1.go = "exit";
			VPVL_Start();
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitão, ficou sabendo? Tem uma garçonete nova trabalhando na nossa taverna. Dizem que ela é muito bonita. Homens de toda parte têm vindo só pra dar uma olhada nela. Mas faz três dias que ela não aparece no trabalho, o que deixou o dono da taverna furioso, já que ele estava ganhando uma fortuna desde que ela chegou. Dizem que ele até paga pra quem encontrar a moça.​";
			link.l1 = "Obrigado, preciso me retirar.";
			link.l1.go = "exit";
			TBP_Start();
			break;
        }
		//<-- Тайна Бетси Прайс
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "Ficou sabendo? Nosso ferreiro perdeu feio no carteado pro Javier Castillo, tanto que ficou pelado, teve que apostar algo muito valioso. Desde então, o ferreiro não conseguiu se recuperar e não aceita mais encomendas – só fica lamentando que o almirante vai arrancar o couro dele. Coitado, todo mundo aqui sabe que não se joga com esse trapaceiro do Castillo!";
			link.l1 = "Obrigado, preciso ir agora.";
			link.l1.go = "exit";
			OZ_Start();
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Você ficou sabendo? O capitão do fluyt 'Águila' deu uma bronca tão grande no imediato lá na taverna que até as paredes tremeram! Parece que o capitão queria zarpar com a maré, mas o imediato deixou toda a tripulação ir pra terra. Agora os marinheiros se espalharam pela cidade, e se não voltarem a tempo, o navio vai partir sem eles – o capitão não vai esperar! Fico pensando, qual será a pressa? Uma carga valiosa, um negócio lucrativo, uma ordem urgente do governador?";
			link.l1 = "Obrigado, preciso ir agora"+GetSexPhrase("","")+".";
			link.l1.go = "exit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("towngirl", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more question I want to ask...","One more question.");
            answ3 = RandPhraseSimple("Well, anything can happen. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Bem, não tenho mais nada pra te contar, deixa eu passar.","Já cansei das suas perguntas, com licença, tenho muitas outras coisas para resolver."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Obrigado, eu devo ir.","Adeus.");
		link.l2.go = "exit";
	break;

/////////////////////////////////////////////////---слухи мещан---////////////////////////////////////////////
	case "rumours_townman":	
		NextDiag.CurrentNode = "rumours";
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Ficou sabendo? Dizem que a filha do Thomas Morrison está de cama faz seis meses. Os médicos não conseguem fazer nada contra a doença dela. A única que pode ajudar é a cigana famosa pelas poções que curam até os mais doentes. Mas ela se recusou completamente a fazer qualquer coisa pela pobre moça.";
			link.l1 = "Obrigado, preciso me retirar.";
			link.l1.go = "exit";
			DWH_Start();
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Dois dias atrás, tentaram matar o Chefe do Porto na maior cara de pau! O assassino ficou esperando na porta do escritório dele, mas o Chefe conseguiu gritar por socorro. Um mosqueteiro apareceu correndo e feriu o sujeito, mas o desgraçado ainda conseguiu fugir pelos portões da cidade.\nDizem que o Chefe do Porto está pagando uma bela recompensa pela cabeça desse canalha! Até agora, ninguém teve coragem de se apresentar. Olha, nem por mil dobrões eu arriscava meu pescoço...";
			link.l1 = "Obrigado, preciso ir agora.";
			link.l1.go = "exit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Ouviu as novidades?! Isso é um absurdo dos grandes! Não sobrou uma gota de rum ou vinho na taverna – como é que alguém vai se aliviar nesse calor infernal? O estalajadeiro vive prometendo há uma semana que a bebida vai voltar a rolar, mas até agora, nada! Querem que a gente fique com a garganta seca até o fim dos tempos?";
			link.l1 = "Obrigado, preciso ir agora.";
			link.l1.go = "exit";
			TPZ_Start();
			break;
        }
		//<-- Торговля по закону
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Dizem por aí no porto que Julie d'Armagnac, a sobrinha do governador, virou só uma sombra do que já foi. Antes cheia de vida e radiante, agora ela vaga pelas ruas com uma tristeza estampada no rosto. O povo comenta e tenta adivinhar o que aconteceu com ela, mas ninguém sabe ao certo. Vai ver algum canalha partiu o coração dela?"+GetSexPhrase(" Será que foi você, Capitão?","")+"";
			link.l1 = ""+GetSexPhrase("Duvido ","")+". Obrigado, preciso me retirar.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
		
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Dizem que o pescador Pierre Carno sumiu sem deixar rastro. Dois dias atrás, ele saiu para o mar e desde então não se teve mais notícia dele. Sua esposa, Lea, está inconsolável. De dia e de noite, ela faz vigília no cais, com os olhos perdidos no horizonte, rezando para ver a vela do seu amado.";
			link.l1 = "Obrigado, preciso me retirar.";
			link.l1.go = "exit";
			VPVL_Start();
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitão, você ficou sabendo? Tem uma garçonete nova trabalhando na nossa taverna. Dizem que ela é uma beleza. Homens de tudo quanto é canto têm aparecido só pra dar uma olhada nela. Mas faz três dias que ela não aparece pro trabalho, o que deixou o dono da taverna furioso, já que ele estava lucrando horrores desde que ela chegou. Dizem que ele até está disposto a pagar pra quem encontrar a moça.​";
			link.l1 = "Obrigado, preciso me retirar.";
			link.l1.go = "exit";
			TBP_Start();
			break;
        }
		//<-- Тайна Бетси Прайс
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "Ficou sabendo? Nosso ferreiro perdeu feio no jogo de cartas pro Javier Castillo, tanto que foi depenado até o osso e teve que apostar algo muito valioso. Desde então, o ferreiro não consegue se recuperar e não aceita mais encomendas – só fica se lamentando que o almirante vai arrancar o couro dele. Coitado, todo mundo aqui sabe que não se joga com aquele trapaceiro do Castillo!";
			link.l1 = "Obrigado, preciso ir agora.";
			link.l1.go = "exit";
			OZ_Start();
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Você ficou sabendo? O capitão da flauta 'Águila' deu uma bronca tão grande no imediato na taverna que até as paredes tremeram! Parece que o capitão queria zarpar com a maré, mas o imediato deixou toda a tripulação ir pra terra. Agora os marinheiros se espalharam pela cidade, e se não voltarem a tempo, o navio vai partir sem eles – o capitão não vai esperar! Fico pensando, qual será a pressa? Uma carga valiosa, um negócio lucrativo, uma ordem urgente do governador?";
			link.l1 = "Obrigado, preciso ir agora"+GetSexPhrase("","")+".";
			link.l1.go = "exit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more question I want to ask...","One more question.");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Ah, não tenho mais nada pra te contar, deixa eu passar.","Já cansei das suas perguntas, com licença, tenho muitos outros assuntos para resolver."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Obrigado, eu vou indo.","Adeus.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////---слухи тёмных личностей---////////////////////////////////////////////
	case "rumours_marginal":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Infelizmente, não tenho mais nada pra te contar, me deixe passar.","Já cansei das suas perguntas, com licença, tenho muitos outros assuntos para resolver."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Obrigado, eu devo ir.","Adeus.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
			if (bOk1 || bOk2){
				
			dialog.text = "Dizem por aí no porto que Julie d'Armagnac, sobrinha do governador, virou só uma sombra do que já foi. Antes cheia de vida e radiante, agora vaga pelas ruas com uma tristeza estampada no rosto. O povo cochicha e se pergunta o que será que aconteceu com ela, mas ninguém sabe ao certo. Vai ver algum canalha partiu o coração dela?"+GetSexPhrase(" Será que foi você, Capitão?","")+"";
			link.l1 = ""+GetSexPhrase("Duvido ","")+". Obrigado, preciso me retirar.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Acredito que deixei meu recado - terminei.","Já cansei das suas perguntas, capitão. Vai arrumar algo melhor pra fazer!"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Obrigado, eu devo ir.","Adeus.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворянок---////////////////////////////////////////////
	case "rumours_noblegirl":	
        srum = SelectRumourEx("noblegirl", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Dizem no porto que Julie d'Armagnac, a sobrinha do governador, virou só uma sombra do que já foi. Antes cheia de vida e brilho, agora anda pelas ruas com uma tristeza estampada no rosto. O pessoal da cidade cochicha e tenta adivinhar o que aconteceu com ela, mas ninguém sabe ao certo. Vai ver algum canalha partiu o coração dela?"+GetSexPhrase(" Será que foi você, Capitão?","")+"";
			link.l1 = ""+GetSexPhrase("Duvido ","")+". Obrigado, preciso me retirar.";
			link.l1.go = "exit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Acredito que deixei meu recado - terminei.","Já cansei das suas perguntas, capitão. Vai arrumar algo melhor pra fazer!"),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Obrigado, eu já vou indo.","Adeus.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
	case "rumours_sailor":	
		NextDiag.CurrentNode = "rumours";

		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Dois dias atrás, houve uma tentativa ousada contra a vida do Chefe do Porto! O assassino ficou à espreita na porta do escritório dele, mas o Chefe conseguiu gritar por socorro. Um mosqueteiro chegou correndo e feriu o bandido, mas o desgraçado ainda conseguiu fugir pelos portões da cidade\nDizem que o Chefe do Porto está oferecendo uma bela recompensa pela cabeça desse canalha! Até agora, ninguém teve coragem de se apresentar. Vous savez, même s'il offrait mille doublons - je n'accepterais pas...";
			link.l1 = "Obrigado, preciso ir agora.";
			link.l1.go = "exit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Você ficou sabendo? O capitão da flauta 'Águila' deu uma bronca tão grande no imediato lá na taverna que até as paredes tremeram! Parece que o capitão queria zarpar com a maré, mas o imediato deixou toda a tripulação ir pra terra. Agora os marinheiros se espalharam pela cidade, e se não voltarem a tempo, o navio vai partir sem eles – o capitão não vai esperar! Fico pensando, qual será a pressa? Uma carga valiosa, um negócio lucrativo, uma missão urgente do governador?";
			link.l1 = "Obrigado, preciso ir agora"+GetSexPhrase("","")+".";
			link.l1.go = "exit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,srum+posrep1,srum+posrep2,RandPhraseSimple("Infelizmente, não tenho mais nada pra te contar, me deixa passar.","Já cansei das suas perguntas, com licença, tenho muitas outras coisas pra resolver."),"block",1,npchar,Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,answ2,answ3,answ4,npchar,Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Obrigado, eu já vou indo.","Adeus.");
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(singing) We're rascals and scoundrels, we're villains and knaves; Drink up me 'earties, yo ho! We're devils and black sheep, we're really bad eggs, Drink up me 'earties, yo ho!! Hey, matey, how are you doing? How is the sea?";
            link.l1 = "Mar? Continua a mesma desgraçada de sempre. Salgada e molhada. Me diz, pra onde foi meu camarada, aquele que alugou um quarto aqui faz pouco tempo? François Gontier era o nome dele.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(cantando) Moça bonita, vem comigo, moça bonita, deita aqui pertinho de mim? Amanhã cedo eu enrolo todas as suas fitas antes de te deixar!";
            link.l1 = "Beba um gole, camarada! Como vai o mar?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "Ah, o mar... Queria estar no seu lugar!";
            link.l1 = "Não vejo problema algum, amigo. Junte-se à minha tripulação quando quiser.";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("Sabe, o rum faz dos homens amigos! Ha-ha!","Depois de um bom gole de rum até o carrasco vai parecer bonito! Ha-ha!","Quando você bebe, você dorme, quando dorme, não peca! Rum e cerveja vão te levar pro céu, então beba, caramba! Ha!");
            link.l1 = "Claro, vamos tomar um gole... Me diga, bom homem, você sabe "+pchar.GenQuest.FindFugitive.Name+"? Ele é um velho camarada meu. Uns caras me disseram que ele tinha se mudado pra cá...";
            link.l1.go = "FindFugitiveHb";
			break;
        }
		//<-- поиск дезертира
		
		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "Novidade? Ha! Você ainda não soube? Nossos soldados pegaram um espião francês. Maldito impostor, tentou se passar por mercador, mas *hic* - nosso comandante é um sujeito duro na queda!";
            link.l1 = "Não me diga! E o que aquele francês estava tentando farejar?";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "É, "+GetAddress_Form(pchar)+" que mundo é esse em que vivemos... Só tem canalha por todo lado!";
			link.l1 = "O que você quer dizer?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы
		
		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "Você ouviu?! Não acredito! O famoso Capitão Fleetwood foi brutalmente assassinado em Londres! Correu atrás da glória, teve tudo e só encontrou a morte... Se tivesse ficado aqui, estaria mais seguro. Eu digo, às vezes é melhor valorizar o que se tem do que sair correndo atrás de dinheiro ou posição, pode confiar no que eu digo, senhor!";
            link.l1 = "Amigo, você sabe onde todo mundo mora na colônia, né?";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<-- Длинные тени старых грехов
		
		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "Então, o herói do dia, Capitão Edgardo Sotta. O que andam dizendo sobre ele? E o que você acha? Estava ansioso para conhecer esse homem.";
			link.l1.go = "Sotta1";
			link.l2 = "Companheiro, por que você está bebendo sozinho? Todo mundo está se juntando pra ver o enforcamento do Matt Bocudo agora mesmo.";
			link.l2.go = "Lutter1";
			break;
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "Escuta, amigo, estou tentando encontrar um tal de Joep van der Vink. Preciso entregar uma mensagem pra ele. Você sabe como ele é ou alguma coisa sobre ele?";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Ficou sabendo? Dizem que a filha do Thomas Morrison está de cama faz seis meses. Os médicos não conseguem fazer nada contra a doença dela. Só quem pode ajudar é aquela cigana famosa pelas poções que curam até os mais doentes. Mas ela se recusou completamente a fazer qualquer coisa pela pobre moça.";
			link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Obrigado, eu devo ir.","É, que rum danado. Tá bom, vou nessa, divirta-se por aqui.");
			link.l2.go = "exit_sit";
			DWH_Start();
		break;
		}
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Dois dias atrás, tentaram matar o Chefe do Porto na maior cara de pau! O assassino ficou de tocaia na porta do escritório dele, mas o Chefe conseguiu gritar por socorro. Um mosqueteiro chegou correndo e feriu o desgraçado, mas o safado ainda conseguiu fugir pelos portões da cidade.\nDizem que o Chefe do Porto está oferecendo uma bela recompensa pela cabeça do bandido! Até agora, ninguém teve coragem de aparecer. Olha, nem por mil dobrões eu arriscava meu pescoço...";
			link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Obrigado, eu já vou indo.","Eh, que rum danado. Tá bom, vou nessa, aproveite aí.");
			link.l2.go = "exit_sit";
			GS_Start();
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Ficou sabendo da novidade?! Isso é um absurdo! Não sobrou uma gota de rum ou vinho na taverna – como é que alguém vai se aliviar nesse calor dos infernos? O estalajadeiro só faz prometer faz uma semana que a bebida vai voltar a correr, mas até agora, nada! Querem que a gente fique com a garganta seca até o fim dos tempos?";
			link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Obrigado, eu já vou indo.","É, que rum danado. Tá bom, vou nessa, divirta-se por aqui.");
			link.l2.go = "exit_sit";
			TPZ_Start();
			break;
        }
		//<-- Торговля по закону
		//--> Старые счёты
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		if (bOk1 || bOk2)
        {
			dialog.text = "Dizem pelos cais que o nosso barman está encrencado! Alguém roubou o gin dele! E não foi só uma garrafa, veja bem, mas um barril inteiro daquela bebida – do tipo que você não encontra em nenhum outro lugar dessas ilhas! Trouxeram direto da Europa, dizem. O velho esperto não conta pra quem estava guardando, mas de uma coisa todo mundo tem certeza: se esse barril não aparecer logo, vai sobrar pro pobre coitado!";
			link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Obrigado, eu preciso ir.","É, que rum danado. Tá bom, vou nessa, divirta-se por aqui.");
			link.l2.go = "exit_sit";
			OS_Start();
			break;
        }
		//<-- Старые счёты
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Dizem por aí no porto que Julie d'Armagnac, a sobrinha do governador, virou só uma sombra do que já foi. Antes cheia de vida e radiante, agora anda pelas ruas com uma tristeza estampada no rosto. O povo comenta, tentando adivinhar o que aconteceu com ela, mas ninguém sabe ao certo. Será que algum canalha partiu o coração dela?"+GetSexPhrase(" Será que foi você, Capitão?","")+"";
			link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Obrigado, eu já vou indo.","É, que rum danado. Tá bom, vou nessa, divirta-se por aqui.");
			link.l2.go = "exit_sit";
			UV_Start();
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Dizem que o pescador Pierre Carno sumiu sem deixar rastro. Dois dias atrás, ele saiu para o mar e desde então não se teve mais notícia dele. A esposa dele, Lea, está fora de si de tanta tristeza. Dia e noite, ela fica de vigia no cais, com os olhos presos no horizonte, rezando para ver a vela do marido aparecer.";
			link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Obrigado, eu devo ir.","É, que rum danado. Tá bom, vou nessa, aproveite aí.");
			link.l2.go = "exit_sit";
			VPVL_Start();
			break;
        }
		//<-- В плену великого улова
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Capitão, já ficou sabendo? Tem uma garçonete nova trabalhando na nossa taverna. Dizem que ela é uma beleza. Homens de tudo quanto é canto têm vindo só pra dar uma olhada nela. Mas faz três dias que ela não aparece pro trabalho, o que deixou o dono da taverna furioso, já que ele estava ganhando uma fortuna desde que ela chegou. Dizem que ele até está disposto a pagar pra quem encontrar a moça.​";
			link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Obrigado, eu devo ir.","É, que rum danado. Tá bom, vou nessa, divirta-se por aqui.");
			link.l2.go = "exit_sit";
			TBP_Start();
			break;
        }
		//<-- Тайна Бетси Прайс
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "Ficou sabendo? Nosso ferreiro perdeu feio no jogo de cartas pro Javier Castillo, tanto que foi depenado até o osso e acabou apostando algo muito valioso. Desde então, o ferreiro não conseguiu se recuperar e não aceita mais encomendas – só vive reclamando que o almirante vai arrancar o couro dele. Coitado, todo mundo aqui sabe que não se joga com aquele trapaceiro do Castillo!";
			link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Obrigado, eu devo ir.","É, que rum danado. Tá bom, vou nessa, divirtam-se por aqui.");
			link.l2.go = "exit_sit";
			OZ_Start();
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Ficou sabendo? O capitão do flibote 'Águila' deu uma bronca tão grande no imediato na taverna que até as paredes tremeram! Parece que o capitão queria zarpar com a maré, mas o imediato deixou toda a tripulação ir pra terra. Agora os marinheiros se espalharam pela cidade, e se não voltarem a tempo, o navio vai partir sem eles – o capitão não vai esperar! Fico pensando, qual será a pressa? Uma carga valiosa, um negócio lucrativo, uma missão urgente do governador?";
			link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Obrigado, eu devo ir.","É, que rum dos diabos. Tá bom, vou nessa, aproveite aí.");
			link.l2.go = "exit_sit";
			LFD_Start();
			break;
        }
		//<-- Письмо от покойника
		//--> LaEspadaDelRey
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LEDR_Start") && npchar.city == "Pirates";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LEDR_Start") && npchar.city == "Pirates";
		if (bOk1 || bOk2)
        {
			dialog.text = "Ouvi falar disso, "+GetSexPhrase("amigo","missy")+"? Tem um velho maluco vagando pela cidade. Diz que foi o único que saiu vivo do naufrágio daquele barco podre lá na Baía de Sabu-Matilla, e agora tá desesperado pra voltar lá. Mas é covarde demais pra ir sozinho. Fica falando sem parar de um esqueleto vestido com roupas tribais que aparece toda manhã e desafia ele pra lutar até a morte. Eu? *hic* Nem por quinhentos dobrões eu ia com ele. Vai saber que tipo de demônio tá dançando na cabeça daquele doido.";
			link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Obrigado, eu devo ir.","É, que rum danado. Tá bom, vou nessa, aproveita aí.");
			link.l2.go = "exit_sit";
			LEDR_Start();
			break;
        }
		//<-- LaEspadaDelRey
		
		Dialog.Text = LinkRandPhrase("Bem... hic! ","Ah, rum bom! ","Bem... ")+SelectRumourEx("habitue",NPChar);
		link.l1 = RandPhraseSimple(RandSwear()+"Isso merece mais uma dose...","Tá bom, vamos tomar mais uma.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Obrigado, eu vou nessa.","É, que rum dos diabos. Tá bom, vou nessa, se divirta por aqui.");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text = NPCStringReactionRepeat(strum,strum+" É. Não tenho mais nada pra contar.",strum+" Agora é melhor eu voltar ao trabalho.",RandPhraseSimple("Já te falei, não tenho tempo pra conversa fiada!","Sou um homem ocupado, não tenho tempo pra fofoca!"),"block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear()+"Interessante! Mas vamos direto ao ponto","Obrigado, e aqui vai mais uma coisa."),pcharrepphrase(""+GetSexPhrase("Maldito seja eu","Interessante")+"! Belo contador de histórias. Mas tenho mais uma pergunta.","Vamos parar de perder tempo e falar de negócios."),pcharrepphrase(RandSwear()+" Mais uma coisa e já vou embora.","Você está certo, tempo é dinheiro."),pcharrepphrase("Só pensa no próprio bolso! Tá bom, mas não perde a cabeça.","Me perdoe. Vamos falar de negócios."),npchar,Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Adeus, seu velho bêbado.","Tchau, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"."),pcharrepphrase("Caramba! Não vá muito longe. Eu volto já.","Prazer em te ver, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"! Adeus!")),NPCharRepPhrase(npchar,pcharrepphrase("Soltem as amarras!","Adeus!"),pcharrepphrase("Ei! O que você está escondendo aí? Rum? Não?! Tanto faz, vou pegar uma bebida pra mim.","Desculpe, tenho assuntos importantes na cidade.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Até mais!","Eu preciso ir. Adeus, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!"),pcharrepphrase("Não ouse discutir comigo! Não quero saber disso!","Acho que é melhor eu dar uma olhada no meu navio. Até mais, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("O que há com você, camarada? Sou eu - "+GetFullName(pchar)+"! Tira um cochilo, depois a gente conversa.","Tenho medo que seu fígado te mate antes de eu voltar aqui de novo."),pcharrepphrase("Conta suas moedas de prata, seu safado! Te vejo depois.","Prazer em te ver, "+GetAddress_FormToNPC(NPChar)+" "+GetFullName(npchar)+"!")),npchar,Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitão",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"Interessante! Tem mais uma coisa que quero perguntar...","Mais uma pergunta.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Obrigado, eu devo ir.","Adeus.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("landcaptain",NPChar);
			Link.l1 = RandPhraseSimple(RandSwear()+"Interessante! Tem mais uma coisa que quero perguntar...","Mais uma pergunta.");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("Obrigado, eu já vou indo.","Adeus.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
				if(startHeroType == 4)
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Você sabe o preço. Informação é como um quarto, comida ou bebida – tem seu valor. Vai te custar mil pesos.","Você sabe o preço. Informação é como um quarto, comida ou bebida – tem seu custo. Isso vai ser mil pesos.","Você sabe o preço. Informação é como um quarto, comida ou bebida – tem seu valor. Isso vai te custar mil pesos."),"Não tenho mais nada a dizer aqui. Agora, com licença, preciso ir.","","","block",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Na verdade, por que estou perguntando isso? Posso perguntar para outra pessoa. Desculpa incomodar você.","Na verdade, por que estou até perguntando? Posso perguntar isso pra outra pessoa. Desculpa incomodar você."),"","","",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000)
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Eu sei, claro. Aqui está o meu pagamento.","Eu sei, claro. Aqui está o meu pagamento."),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("Eu não tenho essa quantia.","","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}
				else
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Informação custa dinheiro. 1000 pesos e eu te conto tudo o que sei.","Minha memória anda meio ruim, mas talvez mil peças de oito me ajudem a lembrar de alguma coisa.","Estou ansioso para compartilhar informações com você. Mas isso vai te custar 1000 peças de oito. Sem pechinchar."),"Não tenho mais nada a dizer aqui. Agora, com licença, preciso ir.","","","block",1,npchar,Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear()+"Não vou pagar por conversa fiada.","Vou pensar em jeitos melhores de gastar esse dinheiro."),"Vamos mudar de assunto.","Vamos mudar de assunto.","Vamos mudar de assunto.",npchar,Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000 )
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Você os terá se eu aprender algo que valha a pena com você.","Eu pago se você me der algo de valor."),"","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 = HeroStringReactionRepeat("Eu não tenho essa quantia.","","","",npchar,Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}

		break;
		
		case "rumours_tavern_yes":
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation"))
			{
				bool bOk = (pchar.questTemp.Saga.BarbTemptation == "silk") || (pchar.questTemp.Saga.BarbTemptation == "give_silk");
				if (bOk && npchar.location == "Marigo_tavern" && !CheckAttribute(npchar, "quest.barbtemptation"))
				{
					AddMoneyToCharacter(pchar, -1000);
					Dialog.Text = " Nossa patrulha destruiu recentemente a brigantina de um contrabandista francês chamado Morel. O homem está agora nas masmorras, esperando pela sentença de morte. Nosso comandante acha que não havia toda a carga no navio dele, então ainda está tentando encontrá-la... o francês só vai morrer quando o comandante achar a carga desaparecida. ";
					link.l1 = "Interessante... Tudo bem, pegue o dinheiro. Tem mais alguma coisa pra dizer?";
					link.l1.go = "rumours_tavern";
					Saga_CreateMorelle(); //ставим Мореля
					npchar.quest.barbtemptation = "true";
					pchar.questTemp.Saga.BarbTemptation.Prison = "true";
					break;
				}
			}	
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && npchar.location == "portobello_tavern")
			{
				DelLandQuestMark(npchar);
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Teve uma grande festa no palácio do governador. O amigo de Sua Excelência, Dom Carlos de Milyar, voltou. Ele foi capturado numa batalha no mar, mas conseguiu escapar com a ajuda de um tenente francês. Dom Carlos não é só esperto, é também um homem muito generoso. Com o apoio dele, esse tenente, Jean Deno, agora virou capitão do 'Sario'. Pelo que ouvi, ainda ganhou uma pequena plantação de presente. Agora o francês virou Juan! Que história, hein!";
				link.l1 = "Interessante... Tudo bem, o dinheiro é seu. Pegue isso. Tem mais alguma coisa pra me contar?";
				link.l1.go = "rumours_tavern";
				pchar.questTemp.FMQG = "headhunter_juan";
				AddQuestRecord("FMQ_Guadeloupe", "10");
				pchar.quest.FMQG_Juanship.win_condition.l1 = "location";
				pchar.quest.FMQG_Juanship.win_condition.l1.location = "PortoBello";
				pchar.quest.FMQG_Juanship.function = "FMQG_CreateJuanship";
				break;
			}	
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "town" && npchar.location == "Marigo_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "O nosso comandante enviou reforços para patrulhar a selva e aumentou o número de guardas na cidade. Dizem que os ingleses estão planejando se infiltrar em Philipsburg e libertar os oficiais capturados.";
				link.l1 = "Não me diga! Eles têm mesmo coragem de fazer uma dessas? E de quais oficiais você está falando exatamente?";
				link.l1.go = "FMQN_r";
				break;
			}	
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Outro dia, a cidade inteira ficou em polvorosa. Um oficial de uma escuna militar ficou completamente bêbado na minha taverna e quase violentou uma mulher casada. Depois, ainda espancou o marido dela, que tentou defendê-la, e chegou a ameaçá-lo com uma espada. Imagina só, tudo isso bem na frente dos guardas da cidade! Como dizem, quem tem poder faz a lei. Os soldados só viraram as costas enquanto esse desgraçado fazia o que queria. Mas o canalha acabou sendo desarmado, veja só, por alguns marinheiros de um navio mercante. Quase amarraram ele direitinho, mas o infeliz conseguiu escapar e se escondeu no navio dele. O Comandante e o Alcalde tentaram abafar o caso, mas o marido revoltado é um cidadão respeitado, que procurou Sua Excelência Dom Diego de Toledo e fez barulho entre a elite local. Expediram um mandado de prisão para o oficial. Dizem que aconselharam o capitão dele a sair do porto com o sujeito e transferir o canalha para outro lugar. Só que o capitão da escuna, Esberdo Cabanas, é um homem de honra. Assim que soube do que o oficial tinha feito, prendeu ele imediatamente e mandou de volta para terra. O desgraçado agora está apodrecendo na cadeia, de onde nunca devia ter saído, se quer saber. E depois, talvez, seja rebaixado a soldado raso e leve uma surra, só para servir de exemplo para os outros.";
				link.l1 = "Espera aí, você disse Capitão Esberdo Cabanas? Hmm... que história interessante, viu! Tá certo, você merece seu dinheiro, aqui está. Tem mais alguma coisa que possa me contar?";
				link.l1.go = "rumours_tavern";
				Mtraxx_CreateOfficer(); // ставим офицера-негодяя
				pchar.questTemp.Mtraxx = "jewelry_4";
				pchar.GenQuest.PrisonQuestLock = "true";
				AddQuestRecord("Roger_1", "7");
				DelLandQuestMark(characterFromId("Havana_tavernkeeper"));
				AddLandQuestMarkToPhantom("havana_prison", "havanaJailOff");
				break;
			}
			// Jason Исла Мона
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "rumours" && rand(2) == 1)
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Dizem que uns criminosos foram largados numa das ilhas desertas! Dizem que são monstros tão cruéis que nem o carrasco nem os padres tiveram coragem de lidar com eles! Mas por que sempre acabam trazendo esse tipo de gente pra cá?!";
				link.l1 = "Hmm... que interessante! Talvez eu devesse ir atrás deles e recrutá-los – sempre preciso de almas desesperadas... Por que essa cara pálida, camarada? Tô brincando, tô brincando... Você ganhou seu dinheiro – aqui está. Ouviu mais alguma coisa interessante?";
				link.l1.go = "rumours_tavern";
				IslaMona_TerksCreateHimenes();
				break;
			}
			// Гаспар во фриплее 
			if ((SandBoxMode) && npchar.city == "Tortuga" && (sti(pchar.reputation.nobility) < 41))
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text = "Sua reputação o precede, capitão. Aposto que muitas vezes teve que quebrar a cabeça pensando onde vender aquelas bugigangas e pedrinhas...";
				link.l1 = "E você sabe quem pode me ajudar com isso?";
				link.l1.go = "About_Gaspar";
				break;
			}
            string RumText = SelectRumourEx("tavern", NPChar); //fix
			
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
				if(startHeroType == 4)
				{
					link.l1 = "Parece que no fim das contas você não sabe de nada. Não achei que você fosse me enganar desse jeito. Nada esperto da sua parte. Bem, adeus.";
				}
				else
				{
					link.l1 = RandPhraseSimple("Lixo inútil. Não vou te pagar um único peso! Adeus.","Sua informação não vale nada, então você não vai ganhar nada.");
				}
			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                AddMoneyToCharacter(pchar, -1000);
                Dialog.Text = RumText;
				if(startHeroType == 4)
				{
					link.l1 = "Sério? Interessante, obrigado. Bem, preciso ir, até a próxima.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("Obrigado, pegue o dinheiro. Mais alguma coisa pra dizer?","Tá bom, pega o dinheiro. Tem mais alguma coisa pra dizer?");
					link.l1.go = "rumours_tavern";
				}
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "Você podia ter ajudado com umas moedas. Diferente de você, Helena, eu não tenho o Barão dos Irmãos me bancando.";
				link.l1 = "Você tem um estabelecimento inteiro. E eu cheguei onde estou sozinho. Bom, tirando o navio, os canhões, a tripulação e os suprimentos que o Barão me deu. Tá bom, deixa pra lá.";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "Me entende, eu preciso alimentar minha família.";
				link.l1 = "Vamos mudar de assunto.";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("Obrigado, eu já vou indo.","Adeus.","Tchau.");
				link.l2.go = "Exit";
			}
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("pobre",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"Interessante. Mais uma pergunta...","Hum, deixa eu perguntar outra coisa...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Bem, adeus.","Tchau, camarada.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Eu já contei tudo o que sabia.","Não tenho mais nada pra contar, desculpe...");
				Link.l1 = RandPhraseSimple("Entendi. Adeus.","Até logo, camarada...");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("pobre",NPChar);
				Link.l1 = RandPhraseSimple(RandSwear()+"Interessante. Mais uma pergunta...","Hum, deixa eu te perguntar outra coisa...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Bem, adeus.","Até mais, camarada.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Eu já te contei tudo o que sei.","Não tenho mais nada pra contar, desculpe...");
				Link.l1 = RandPhraseSimple("Entendi. Adeus.","Entendido. Adeus, camarada...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC",NPChar);
				Link.l1 = RandPhraseSimple("Entendi...","Entendi...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar,RandPhraseSimple("Eu já te contei tudo que eu sabia.","Não ouvi nada de novo, desculpe..."),RandPhraseSimple("Eu já contei tudo o que eu sabia.","Não ouvi nada novo, desculpa..."));
				Link.l1 = RandPhraseSimple("Entendi, então adeus.","Entendido. Adeus.");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("Ei, capitão! Sempre é bom conversar com você. Ficar sozinho aqui pode ser bem entediante às vezes...","Eu moro sozinho, visitas são raras. Por isso, estou sempre com vontade de conversar."),"Gosta de conversar, capitão? Bem, talvez eu tenha mais alguma coisa pra te contar...","Traga uma garrafa de rum da próxima vez que vier me ver. Conversa boa é com um gole...","Já te contei tudo o que sei. Não tenho mais nada a acrescentar.","block",1,npchar,Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Então compartilhe sua informação. Eu gosto de conversar com as pessoas, sabia...","Me conta! Como dizem, quem tem a informação tem o mundo?"),"Tipo o quê?","Claro! Tem mais alguma coisa pra contar?","Tá bom, pelo menos tivemos uma boa conversa.",npchar,Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Obrigado! Mais alguma coisa?","Muito interessante! Tem mais alguma coisa?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Obrigado! Isso foi bem divertido...","Obrigado por me contar!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("Obrigado! Mais alguma coisa?","Muito interessante! Mais alguma coisa?");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Obrigado! Isso foi bem divertido...","Obrigado por me contar!");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Obrigado! Mais alguma coisa?","Muito interessante! Mais alguma coisa?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Obrigado! Isso foi bem divertido...","Obrigado por me contar!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "Mas onde está o pacote? Você não está com ele?";
	        	link.l1 = "Bem... Era pra eu entregar isso pra você. Mas acabou que... pra ser bem sincero, tiraram de mim. Não consegui reagir e eu mesmo entreguei o pacote praqueles atacantes. ";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)//раскрыли обман
			{
				dialog.text = "Hm. Com licença, mas o pacote já tinha sido aberto antes! Isso está mais do que claro pra mim. O selo foi re-lacrado...";
	        	link.l1 = ""+GetAddress_FormToNPC(NPChar)+", é o pacote que me deram no escritório do porto de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+", e eu não faço a menor ideia...";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));//сильно снижаем оплату
				dialog.text = "Eu estava esperando por você. Mas você está "+FindRussianDaysString(iTime)+" tarde! A informação que você trouxe já não é tão útil... Ainda tem algum valor, claro, então vou te pagar "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+". Por favor, aceite o dinheiro e adeus.";
	        	link.l1 = "Obrigado. Acho que sim.";
	        	link.l1.go = "Postcureer_LevelUp_complete";
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "8");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(iTime));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "lost")//опоздали совсем
			{
				dialog.text = "Então é você! Estive esperando por você já faz um bom tempo, até tomei providências para recuperar o pacote. Me entregue ele. Agora eu realmente não preciso mais dele, graças à sua chegada, mas gostaria de ficar com ele para mim\nComo você deve entender, não posso te pagar nada, mas vou garantir que seu bom nome seja restaurado.";
	        	link.l1 = "Obrigado... Eu acho. Me desculpe pela demora, de verdade. Adeus.";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "Eu estava esperando por você. Chegou na hora certa, a informação que me trouxe vai ser muito útil. Por favor, aceite este dinheiro pelo seu trabalho - "+FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money))+". Agradeço pela sua chegada na hora certa.";
        	link.l1 = "De nada. Até logo!";
        	link.l1.go = "Postcureer_LevelUp_complete";
			pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			AddQuestRecord("Postcureer", "10");
		break;
		
		case "Postcureer_LevelUp_complete":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 120);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 120);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_bad":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "9");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 33);
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_fail":
			dialog.text = "Ah, eu sabia que ia acabar assim... Devia ter contratado um navio de correio militar, não um capitão civil... Tanto faz, "+GetAddress_Form(NPChar)+", você não é um soldado, então não há nada pelo que te culpar. Adeus.";
			link.l1 = "Até logo, "+GetAddress_FormToNPC(NPChar)+".";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail":
			dialog.text = "Senhor, eu conheço o mestre do porto de "+XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+" pessoalmente, ele é um homem honesto. Além disso, não havia motivo para ele abrir o pacote. "+GetAddress_Form(NPChar)+", você é um farsante! Não vou te pagar nem um tostão. Cai fora!";
			link.l1 = "Hm...";
			link.l1.go = "Postcureer_LevelUp_complete_Agentfail_1";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail_1":
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "17");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.AgentChance");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
// <--почтовый генератор 2 уровня

//Jason --> ---------------------------------генератор Неудачливый вор--------------------------------------------
		case "Device_Common":
			dialog.text = "Parecia um lixo ambulante. Um vagabundo ou um miserável. Não sei dizer pra onde foi, não me dei ao trabalho de seguir.";
			link.l1 = "Melhor do que nada. Obrigado! Preciso ir.";
			link.l1.go = "Device_Common_1";
		break;
		
		case "Device_Common_1":
			string sNation = pchar.GenQuest.Device.Shipyarder.Nation;
			sld = GetCharacter(NPC_GenerateCharacter("Device_poorman", "panhandler_"+(rand(5)+1), "man", "man", sti(pchar.rank)+5, sNation, 20, true, "quest"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+5, true);         
			GiveItem2Character(sld, "slave_02");
			EquipCharacterbyItem(sld, "slave_02");
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, sNation+"_CITIZENS");
			sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; 
			sld.dialog.currentnode = "Device_poorman"; 
			sld.greeting = "Gr_poorman";
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance2))
			{
				case 0://в городе
					sld = characterFromId("Device_poorman");
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City +"_town", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				break;
				case 1://за воротами
					sld = characterFromId("Device_poorman");
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_ExitTown", "goto", "goto1");
				break;
				case 2://в бухте
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
				break;
				case 3://в доме
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Location = GetDeviceLocation(npchar); //определяем локацию
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Location, "goto", "goto1");
					if (pchar.GenQuest.Device.Shipyarder.Location == "none" || CheckAttribute(pchar, "GenQuest.SeekSpy.Location"))//если вдруг мимо или взят поиск шпиона
					{
						pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
					}
				break;
			}
			pchar.GenQuest.Device.Shipyarder = "inSeek";
			DialogExit();
			AddQuestRecord("Device", "9");
		break;
		//<-- генератор Неудачливый вор
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN_r":
			DelLandQuestMark(npchar);
			if (GetNationRelation(SPAIN, ENGLAND) == RELATION_NEUTRAL) {"Not long ago, an English ship was intercepted off the coast of Sint Maarten, and aboard it were several high‑ranking officers. They planned to send them to Willemstad pending investigation, but for the time being they were locked up in prison. There’s word that one of the captured soldiers, in exchange for his freedom, told the commandant that the English intended to send in a sabotage team and stage a jailbreak. They even had their plan ready. So our brave commandant is keeping a sharp lookout. If such important birds fly the coop — he’ll surely be stripped down to a common soldier. That’s not all — we can’t afford another war starting again.";}
			else {Dialog.Text = "Not long ago, an English vessel was captured in the waters of Sint-Maarten; she was carrying a few high-ranking officers. It was decided to send them to Willemstad, but at this moment they are being held here in our comfortable dungeons. They say that one of the captured soldiers told our commandant about the English intention to send a raiding party here to rescue the officers. That's why our good old commandant is ready and armed. Why wouldn't he be? If the prisoners escape, he'll be demoted to a common soldier!";}
			link.l1 = "Interessante... Tudo bem, o dinheiro é seu. Pegue isto. Tem mais alguma coisa que queira me contar?";
			link.l1.go = "rumours_tavern";
			pchar.questTemp.FMQN = "governor";
			pchar.quest.FMQN_governor.win_condition.l1 = "location";
			pchar.quest.FMQN_governor.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_governor.function = "FMQN_ToGovernor";
			if (Whr_IsDay()) AddDialogExitQuest("FMQN_GetRumoursDay");
			else AddDialogExitQuest("FMQN_GetRumoursNight");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квесты мэра, проникновение во враждебный город
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple("Muito bem então. Tenho o pacote aqui, pronto para entrega. Pegue\nNão volte aqui e nem fale mais comigo, é perigoso demais. Se cuide por aí...","Hm, muito bem. Pegue o pacote e certifique-se de entregá-lo ao homem de quem acabamos de falar\nAdeus, e não fale mais comigo, é perigoso demais.");
            link.l1 = RandPhraseSimple("Entendi. Adeus...","Boa sorte e até logo.");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Voc")); // belamour gen
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Гаспар во фриплее
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "About_Gaspar":
			dialog.text = "Eu sei. O nome dele é Gaspar Parmentier, mas os amigos o chamam de Dente de Ouro. Ele é um homem confiável e, o mais importante, compra em quantidades tão grandes que nenhum agiota jamais sonharia. Tenho certeza de que vocês vão se entender rapidamente. Só lembre-se: ele não gosta de estranhos. Então, se for procurá-lo, mencione que foi indicado por mim. A casa dele fica perto da administração portuária.";
			link.l1 = "Bom, você mereceu seu dinheiro — aqui está. Sabe de mais alguma coisa interessante?";
			link.l1.go = "rumours_tavern";
			AddDialogExitQuestFunction("CreateGaspar_Sandbox");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Грабеж среди бела дня, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("Um assalto em plena luz do dia?! Sério?! Fica aí onde está, camarada...","Ei, o que você está fazendo aí?! Parece que alguém ia me roubar. Agora você está acabado...","Espera, pra onde você vai? Um ladrão! Acabou pra você, camarada...");
			link.l1 = LinkRandPhrase("Merda!","Caramba!","Droga!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идёт распределение по городам
{
	string sRetRumour = "Oh, seems like you've found a bug. Contact Jason and tell him about it, look for a 'Blackmark'.";
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;
		
		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;
		
		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;
		
		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;
		
		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;
		
		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;
		
		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;
		
		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;
		
		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;
		
		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;
		
		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;
		
		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;
		
		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;
		
		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;
		
		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;
		
		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;
		
		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;
		
		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;
		
		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;
		
		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;
		
		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;
		
		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;
		
		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}
	
	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // База слухов жителей. Можно менять без новой игры
{
	
	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = "Oh, sir governor is an excellent man. He manages our colony with great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is... well... he is quite thrifty. It might be just another virtue though.";
	STR_MAYOR[1] = "Oh, sir governor is an excellent man. He manages our colony with great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is... well... he is quite thrifty. It might be just another virtue though.";
	STR_MAYOR[2] = "Our governor is a good man but he is weak character. If he had a little firmness in his soul, our merchants could've got small tax breaks ... And it's already time to allocate subsidies for repairing the fort.";
	STR_MAYOR[3] = "Hmm ... He's recently become our governor. He is quite young and therefore very initiative. With him our colony is flourishing.";
	STR_MAYOR[4] = "Our governor is still relatively young. They say he is a good-for-nothing younger son of a Spanish count, sent far away from the yard to stop shaming his family. He has been appointed here quite recently, and didn't have time to create anything memorable.";
	STR_MAYOR[5] = "Hmm ... He's recently become our governor. He is quite young and therefore very initiative. With him our colony is flourishing";
	STR_MAYOR[6] = "Well... Nothing... I can't say anything bad about him...";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Hm, I wouldn't trust my property to this rogue. Don't misunderstand me, but it seems to me that this is the most unreliable person in our town\nI heard he's working with pirates and smugglers whom often can be seen in his tavern.";
	STR_TAVERNKEEPER[1] = "What can we say about him! Cowardly, also not the smartest person I know. Besides, he is greedy for money, which is why he constantly gets into various troubles! But he is always up to date with all the news.";
	STR_TAVERNKEEPER[2] = "Quite a pleasant guy. It is always nice spending time in his tavern, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[3] = "Incredible man. He shouldn't keep a tavern but should be an informant for intelligence office. Sometimes it seems that he knows literally everything that happens in our town. It even scares me.";
	STR_TAVERNKEEPER[4] = "I don't know what to tell you. A man. Keeps a tavern. Knows everything about the town and its citizens.";
	STR_TAVERNKEEPER[5] = "They say that one can rely on it. On the other hand, I heard that he doesn't like unnecessary risk and always careful in doing his business. Yes, and dark affairs is not his type of business.";
	STR_TAVERNKEEPER[6] = "He's got the tavern from his father. His father kept a tavern not far from here, on the island of Highrock on another archipelago. Then his father moved here, built a new tavern here, and now his son runs it..";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Builds ships. I dunno. He's a quiet and peaceful. I guess, he's a good man.";
	STR_SHIPYARDER[1] = "Builds ships. I dunno. He's a quiet and peaceful. I guess, he's a good man.";
	STR_SHIPYARDER[2] = "A good man, but they say that he is too harsh. Constantly scolds all employees. Therefore, they often leave. Still, in spite of this, he is an excellent shipbuilder.";
	STR_SHIPYARDER[3] = "He is a very educated person. I heard that he studied shipbuilding in England, then in Holland. And in the end, he ended up here - far from the metropolis, in the provincial archipelago\nPeople say that he had troubles with the Holy Inquisition, and he had to flee to the colony.";
	STR_SHIPYARDER[4] = "This old man has to retire already and give the road for some fresh blood. He constantly dreams of past times, and grumbles when someone orders something from him besides caravels or galleons.";
	STR_SHIPYARDER[5] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place.";
	STR_SHIPYARDER[6] = "He was a prisoner, exiled from Europe to our colony until it turned out that he had a talent for shipbuilding. After two magnificent brigs had been built under his leadership at the shipyard of our colony, he was forgiven for his transgressions, and now he is a full member of our society.";
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "I can't say anything bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[1] = "He is the main supplier of our governor, and this gives him a good income. But he conducts his affairs honestly. Well, at least he hasn't been noticed in anything shaming for him.";
	STR_TRADER[2] = "This fat man has a big respect in our city. His goods are always excellent, and I don't remember a single case he has ever cheated someone.";
	STR_TRADER[3] = "He's good-for-nothing, really. Trades, but no sense. Sometimes one good is out of stock, sometimes another, sometimes a half of goods... He can't even get himself out of debts.";
	STR_TRADER[4] = "He is not a good man, monsieur. I heard that he was Piere Thiers's right hand, previous trader, but he ruined his business it and then bought the store. I don't know how about the quality of the goods that he sells, but as a person he is very unpleasant to me.";
	STR_TRADER[5] = "Oh! He is an ugly man, I wouldn't advise you to have any business with him\nHe keeps a half of the inhabitants of our city in debt! And the goods those are sold in his store are always of poor quality.";
	STR_TRADER[6] = "Nobody really knows anything about him. He has recently moved here, and immediately opened his business. Trades honestly, wasn't caught at smuggling.";
	
	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];
	
	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}

string GetDeviceLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест по доставке малявы или шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}
