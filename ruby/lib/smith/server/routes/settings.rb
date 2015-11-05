#  File: settings.rb
#  Sinatra routes for handling settings
#
#  This file is part of the Ember Ruby Gem.
#
#  Copyright 2015 Autodesk, Inc. <http://ember.autodesk.com/>
#  
#  Authors:
#  Jason Lefley
#  Richard Greene
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  THIS PROGRAM IS DISTRIBUTED IN THE HOPE THAT IT WILL BE USEFUL,
#  BUT WITHOUT ANY WARRANTY; WITHOUT EVEN THE IMPLIED WARRANTY OF
#  MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.  SEE THE
#  GNU GENERAL PUBLIC LICENSE FOR MORE DETAILS.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.

module Smith
  module Server

    class Application < Sinatra::Base

      helpers do
=begin
        def validate_command(command)
          return unless command.nil? || command.strip.empty?
          halt 400, { error: 'Command parameter is required' }.to_json
        end
=end
      end

      get '/settings' do
        content_type 'application/json'
        begin
          File.read(Settings.smith_settings_file)
        rescue Smith::Printer::CommunicationError => e
          halt 500, { error: e.message }.to_json
        end
      end

      put '/settings' do
        content_type 'application/json'
        begin
          begin
            settings = JSON.parse(@params.keys.first)
          rescue JSON::ParserError => e
            halt 400, { error: e.message }.to_json
          end
          Printer.write_settings_file(settings)
          Printer.apply_settings_file
          puts "status = #{@response.status}"
        rescue Smith::Printer::CommunicationError => e
          halt 500, { error: e.message }.to_json
        end
      end

    end
  end
end
